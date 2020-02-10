# Embedded NN

## 该库有以下几个文件夹:

1. **1_demo**:是最初的demo工程其目的是测试CubeMX能否针对L431正常生成工程, 代码仅有闪灯(PC13)功能
2. **2_regressor_test**:这是第一个跑通的神经网络工程,  里面固化了一个单输入单输出的线性回归神经网络
3. 3_regressor_original:这是从CubeMX直接生成的工程, 里面配置了串口2和神经网络,用于和下面的对比
4. 4_regressor_original_comparison:与上一个工程进行对比, 之缺少了神经网络的功能
5. **5_migration_test**
6. h5:里面存放着Keras生成的.h5文件, 供CubeMX生成固化神经网络
7. help:存放README依赖的图片等
8. validate_nn_6:YouTube的ST频道有个教程, 里面的工程就是这个

## regressor_test

**开发板**:小熊派L431RCT6 256KB 64KB 80MHz

该工程实现了一个简单的神经网络样例, 连接**串口二**后输出神经网络的计算结果:
(输入为随机数)

![Annotation 2020-01-17 214126](https://github.com/wangzilinn/200116_MCU_NN_learn/blob/master/help/Annotation%202020-01-17%20214126.png)

该神经网络具有一个神经元, 单输入, 单输出.

该神经元是由Keras训练得到的, 其参数为:

```
weights: [[0.36967745]] biases: [2.001801]
```

经验证input * weights + biases == output, 其计算结果准确.



## 备注数据:

1. L431RB

2. RCC: HSE, PLL倍频:×20, PLLCLK, HCLK==80MHz

3. HAL_MspInit()只初始化RCC,其余外设的初始化都放在了各自的Msp函数中

4. CRC初始化代码:

   ```c
   /* Private variables ---------------------------------------------------------*/
   CRC_HandleTypeDef hcrc;
   static void MX_CRC_Init(void);//声明
   main(){...}
   static void MX_CRC_Init(void)
   {
   
     /* USER CODE BEGIN CRC_Init 0 */
   
     /* USER CODE END CRC_Init 0 */
   
     /* USER CODE BEGIN CRC_Init 1 */
   
     /* USER CODE END CRC_Init 1 */
     hcrc.Instance = CRC;
     hcrc.Init.DefaultPolynomialUse = DEFAULT_POLYNOMIAL_ENABLE;
     hcrc.Init.DefaultInitValueUse = DEFAULT_INIT_VALUE_ENABLE;
     hcrc.Init.InputDataInversionMode = CRC_INPUTDATA_INVERSION_NONE;
     hcrc.Init.OutputDataInversionMode = CRC_OUTPUTDATA_INVERSION_DISABLE;
     hcrc.InputDataFormat = CRC_INPUTDATA_FORMAT_BYTES;
     if (HAL_CRC_Init(&hcrc) != HAL_OK)
     {
       Error_Handler();
     }
     /* USER CODE BEGIN CRC_Init 2 */
   
     /* USER CODE END CRC_Init 2 */
   
   }
   ```

   

1. CRC的MSP初始化代码:

   ```c
   /**
   * @brief CRC MSP Initialization
   * This function configures the hardware resources used in this example
   * @param hcrc: CRC handle pointer
   * @retval None
   */
   void HAL_CRC_MspInit(CRC_HandleTypeDef* hcrc)
   {
     if(hcrc->Instance==CRC)
     {
     /* USER CODE BEGIN CRC_MspInit 0 */
   
     /* USER CODE END CRC_MspInit 0 */
       /* Peripheral clock enable */
       __HAL_RCC_CRC_CLK_ENABLE();
     /* USER CODE BEGIN CRC_MspInit 1 */
   
     /* USER CODE END CRC_MspInit 1 */
     }
   
   }
   
   /**
   * @brief CRC MSP De-Initialization
   * This function freeze the hardware resources used in this example
   * @param hcrc: CRC handle pointer
   * @retval None
   */
   void HAL_CRC_MspDeInit(CRC_HandleTypeDef* hcrc)
   {
     if(hcrc->Instance==CRC)
     {
     /* USER CODE BEGIN CRC_MspDeInit 0 */
   
     /* USER CODE END CRC_MspDeInit 0 */
       /* Peripheral clock disable */
       __HAL_RCC_CRC_CLK_DISABLE();
     /* USER CODE BEGIN CRC_MspDeInit 1 */
   
     /* USER CODE END CRC_MspDeInit 1 */
     }
   
   }
   ```

   HAL_CRC_MspInit()函数的调用链:

   main()==>MX_CRC_Init()==>HAL_CRC_Init()==>HAL_CRC_MspInit()[在msp.c文件中编写]



## 工程差别记录

1. `\Inc`新增了文件:
   1. app_x-cube-ai.h
   2. constants_ai.h
   3. [network_name].h
   4. [network_name]_data.h
   5. RTE_Components.h//删除该文件无影响
2. `\Src`文件增加了`app_x-cube-ai.c`, `[network_name].c`,`[network_name]_data.c`
3. `\Src`中的`stm32l4xx_hal_msp.c`初始化了CRC
4. `main()`中调用了`MX_CRC_Init()`和`MX_X_CUBE_AI_Init()`, 并include了`"app_x-cube-ai.h"`
5. `\Inc\stm32l4xx_hal_conf.h` 取消注释了`#define HAL_CRC_MODULE_ENABLED`模块
6. 新增了Middlewares文件夹及相关文件

## 迁移过程

1. 移动\Inc
2. 添加那CRC.c
3. 粘贴了Middlewares, keil增加middlewares的include,
4.  将.lib文件加入group
5. main()中
   1. 加入#include "app_x-cube-ai.h"头文件
   2. 加入MX_X_CUBE_AI_Init();初始化
   3. while(1)中执行MX_X_CUBE_AI_Process()函数
6. 

