//
// Created by neowa on 2024/4/27.
//

#include "mpu6050.h"

extern  I2C_HandleTypeDef hi2c1;


int mpu6050_Init(mpu6050_t *mpu){
    uint8_t check;
    HAL_I2C_Mem_Read(&hi2c1,MPU6050_ADDR,WHO_AM_I,1,&check,1,1000);
    if (check==0x68){
        check = 0x00;
        HAL_I2C_Mem_Write(&hi2c1,MPU6050_ADDR,PWR_MGMT_1,1,&check, 1,1000);// 唤醒
        check = 0x07;
        HAL_I2C_Mem_Write(&hi2c1,MPU6050_ADDR,SMPLRT_DIV,1,&check, 1,1000);// 1Khz的速率
        check = 0x00;
        HAL_I2C_Mem_Write(&hi2c1,MPU6050_ADDR,ACCEL_CONFIG,1,&check, 1,1000);// 加速度配置
        check = 0x00;
        HAL_I2C_Mem_Write(&hi2c1,MPU6050_ADDR,GYRO_CONFIG,1,&check, 1,1000);// 陀螺配置
        check = 0x01;
        HAL_I2C_Mem_Write(&hi2c1,MPU6050_ADDR,MPU_INT_EN_REG,1,&check, 1,1000);//开启中断
        check = 0X9c;
        HAL_I2C_Mem_Write(&hi2c1,MPU6050_ADDR,MPU_INTBP_CFG_REG,1,&check, 1,1000);//高电平触发
        return 0;
    }
    return -1;
}