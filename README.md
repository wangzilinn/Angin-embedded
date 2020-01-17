# Embedded NN

## 该库有以下几个文件夹:

1. **demo**:是最初的demo工程其目的是测试CubeMX能否针对L431正常生成工程, 代码仅有闪灯(PC13)功能
2. h5:里面存放着Keras生成的.h5文件, 供CubeMX生成固化神经网络
3. help:存放README依赖的图片等
4. **regressor_test**:这是第一个跑通的神经网络工程,  里面固化了一个单输入单输出的线性回归神经网络
5. validate_nn_6:YouTube的ST频道有个教程, 里面的工程就是这个

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

