SPI

一.分类：

1.软件SPI: 用普通GPIO口模拟SPI接口

2.硬件SPI: 只需要设置正确的SPI时序模式，底层的通信时序由SPI硬件处理



二.相关参数：

1.Mode: Full-Duplex(全双工)  Half-Duplex(半双工)

2.Data Size(数据帧长度 Bit)：选用8Bit或16Bit

3.First Bit(起始位顺序)：MSB(Most Significant Bit 高位先行)  LSB(Least Significant Bit 低位先行)

4.Clock Polarity(CPOL 时钟极性)：取值为0或1， 置0时SCK空闲状态为低电平，置1为高电平

5.Clock Phase(CPHA 时钟相位)：取值为0或1，置0时主机和从机在第一个边沿采集数据，置1时在第二个边沿采集, MOSI和MISO的数据是在读取数据的前一个边沿时刻发生变化的

6.Advanced Parameters: 保持默认



CSDN博客：https://blog.csdn.net/That_Assassin/article/details/135380072