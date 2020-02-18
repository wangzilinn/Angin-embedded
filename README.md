# Embedded NN

## 该库有以下几个文件夹:

1. **1_demo**:是最初的demo工程其目的是测试CubeMX能否针对L431正常生成工程, 代码仅有闪灯(PC13)功能
2. **2_regressor_test**:这是第一个跑通的神经网络工程,  里面固化了一个单输入单输出的线性回归神经网络
3. 3_regressor_original:这是从CubeMX直接生成的工程, 里面配置了串口2和神经网络,用于和下面的对比
4. 4_regressor_original_comparison:与上一个工程进行对比, 之缺少了神经网络的功能
5. **5_migration_test** 该工程是把第3项中的神经网络部分移植到第4项中的一个测试
6. **6_classifier_test**:这是一个运行MNIST数据集的神经网络工程, 并已经进行了测试.
7. **7_LSTM_test**:实现了LSTM
8. h5:里面存放着Keras生成的.h5文件, 供CubeMX生成固化神经网络
9. img:存放README依赖的图片等
10. validate_nn_6:YouTube的ST频道有个教程, 里面的工程就是这个

## 运行环境:

1. Keil 5.27
2. CubeMX 5.50
3. 编译器:6.13.1(强烈建议使用6及以上版本的编译器,编译爽翻天)
4. RCC: HSE, PLL×20, PLLCLK, HCLK==80MHz

## 神经网络最小功能测试:

源码见**2_regressor_test**文件夹.

**开发板**:小熊派L431RCT6 256KB 64KB 80MHz

该工程实现了一个简单的神经网络样例, 连接**串口二**后输出神经网络的计算结果:
(输入为随机数)

![Annotation 2020-01-17 214126](https://github.com/wangzilinn/200116_MCU_NN_learn/blob/master/img/Annotation%202020-01-17%20214126.png)

该神经网络具有一个神经元, 单输入, 单输出.

该神经元是由Keras训练得到的, 其参数为:

```
weights: [[0.36967745]] biases: [2.001801]
```

经验证input * weights + biases == output, 其计算结果准确.



## MNIST测试

源码见6_classifier_test文件夹

**开发板**:小熊派L431RCT6 256KB 64KB 80MHz

该工程实现了一个简单的分类器,输入28*28像素的单个阿拉伯数字图片, 连接**串口二**后输出神经网络的识别概率:

输入图片:

![6](https://github.com/wangzilinn/200116_MCU_NN_learn/blob/master/img/mnist_6.png)

该神经网络具有三层结构:

1. 第一层到第二层为784输入(为图片像素展成的一维数组), 32输出, 
2. 第二层到第三层32输入, 10输出(为每个数字的概率, 

训练该网络的详细代码见[keras_learn](https://github.com/wangzilinn/201114_keras_learn)的readme, 

该库还写了一个简单的代码生成器, 用于生成单片机所需的输入参数.

对于上面的图片, 单片机的输出的结果为:

| 数字  | 概率         |
| ----- | ------------ |
| 0     | 0.011202     |
| 1     | 0.000288     |
| 2     | 0.003477     |
| 3     | 0.004369     |
| 4     | 0.000385     |
| 5     | 0.076738     |
| **6** | **0.897352** |
| 7     | 0.000079     |
| 8     | 0.005681     |
| 9     | 0.000429     |

可以看出, 单片机可以很好的完成手写数字识别的功能

其生成的网络占用空间为:

​	Flash: 101.8 KByte

​	RAM: 168 Byte

## LSTM测试:

输入20个时间点, 每个时间点有单个参数, 即sin(),  预测输出20个时间点, 即cos()

输入:

0.0000, 0.0318, 0.0637, 0.0955, 0.1273, 0.1592, 0.1910, 0.2228, 0.2546, 0.2865, 0.3183, 0.3501, 0.3820, 0.4138, 0.4456, 0.4775, 0.5093, 0.5411, 0.5730, 0.6048

输出:

0.021437  0.522149  1.087820  0.992776  0.989927  1.002372  0.995649  0.973917  0.962171  0.957946  0.952693  0.945284  0.936054  0.924734  0.911672  0.897318  0.881727  0.865241  0.848155  0.830363  

## 有神经网络的工程修改了哪些文件?

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

## 将神经网络迁移至无神经网络的工程:

>  [神经网络]工程为CubeMX生成的带神经网络的工程

>  [无神经网络]工程为CubeMX生成的不带神经网络的工程

步骤:

1. 将[神经网络]工程的`\Inc`文件夹下的:

   1. app_x-cube-ai.h
   2. constants_ai.h
   3. [network_name].h
   4. [network_name]_data.h

   文件复制到[无神经网络]工程相同路径

2. 将[神经网络]工程的`\Src`文件夹下的:

   1. app_x-cube-ai.c
   2. [network_name].c
   3. [network_name]_data.c

   文件复制到[无神经网络]工程相同路径

3. 新建文件夹`\Middlewares\AI`(用于放置AI接口), 将[神经网络]工程的`Middlewares\ST\AI`路径下的

   1. `Inc`文件夹
   2. `Lib`文件夹

   复制到[无神经网络]工程的`\Middlewares\AI`路径下

4. 检查[神经网络]工程下的`\Drivers\STM32L4xx_HAL_Driver\Src`文件夹及`\Drivers\STM32L4xx_HAL_Driver\Src`文件夹, 这两个文件夹应包含启用CRC必须的文件:

   1. stm32l4xx_hal_crc.h

   2. stm32l4xx_hal_crc_ex.h

   3. stm32l4xx_hal_crc.c

   4. stm32l4xx_hal_crc_ex.c

----

以上文件移动完成, 接下来是Keil内部的工程的配置:

----

5. Add Existing Files to Group `Application/User`, 添加`\Src`下的:

   1. app_x-cube-ai.c
   2. [network_name].c
   3. [network_name]_data.c

   **注意**:这里不要图省事全选添加, 否则会把不应该加进去的system_stm32l4xx.c文件也加到这个Group中(这个文件是在Drivers/CMSIS这个Group中的

6. Add Existing Files to Group `Drivers/STM32xxx_HAL_Driver`, 添加`\Drivers\STM32L4xx_HAL_Driver\Src`文件夹下的

   1. stm32l4xx_hal_crc.c
   2. stm32l4xx_hal_crc_ex.c

   文件(在步骤4检查过)

7. Add Group, 并命名为`lib`(这个Group用于放置CubeMX编译好的神经网络静态链接库), Add Existing Files to Group `lib`, 添加`\Middlewares\AI\Lib`文件夹下的NetworkRuntime500_CM4_Keil.lib

8. Options for Target '[无神经网络]工程',->C/C++选项卡,->Include Paths->添加`../Middlewares/AI/Inc`(在第3步新建的)

----

以上Keil配置完成, 下面修改.c文件

----

9. 在stm32l4xx_hal_conf.h文件中取消`#define HAL_CRC_MODULE_ENABLED  `模块的注释

10. 在stm32xxxx_hal_msp.c文件中新增CRC的MSP初始化代码:

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

11. 在main.c加入#include "app_x-cube-ai.h"头文件

12. 在main.c中新增CRC的初始化代码:

    ```c
    /* Private variables ---------------------------------------------------------*/
    CRC_HandleTypeDef hcrc;
    static void MX_CRC_Init(void);//记得声明
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

13. 在main中初始化CRC, 初始化神经网络, 在while(1)中执行神经网络:

    ```c
    int main(void)
    {
      HAL_Init();
      SystemClock_Config();
      MX_CRC_Init();//初始化CRC
      MX_X_CUBE_AI_Init();//初始化神经网络
      while (1)
      {
        MX_X_CUBE_AI_Process();//开始执行神经网络
      }
    }
    ```

14. 迁移完成.

## 将一个新的神经网络放到原来的工程中:

只用执行上面的第1, 2步, 并解决冲突即可.

## 备忘录

1. HAL_CRC_MspInit()函数的调用链:6_

   main()==>MX_CRC_Init()==>HAL_CRC_Init()==>HAL_CRC_MspInit()[位于stm32xxx_HAL_msp.c]

2. HAL_MspInit()只初始化RCC,其余外设的初始化都放在了各自的Msp函数中

3. 





