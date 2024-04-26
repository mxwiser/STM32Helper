//
// Created by neowa on 2024/4/27.
//

#include "mpu6050.h"
#include "main.h"
extern  I2C_HandleTypeDef hi2c1;
typedef struct {
    //need pre-setting
    float dt;
    float q_filter;
    uint8_t address;

} mpu6050_t;

int mpu6050_Init(mpu6050_t *mpu){
    uint8_t check;
    HAL_I2C_Mem_Read(&hi2c1,(*mpu).address,WHO_AM_I,1,&check,1,1000);
    if (check==0x68){
        check = 0x00;
        HAL_I2C_Mem_Write(&hi2c1,(*mpu).address,PWR_MGMT_1,1,&check, 1,1000);// 唤醒
        check = 0x07;
        HAL_I2C_Mem_Write(&hi2c1,(*mpu).address,SMPLRT_DIV,1,&check, 1,1000);// 1Khz的速率
        check = 0x00;
        HAL_I2C_Mem_Write(&hi2c1,(*mpu).address,ACCEL_CONFIG,1,&check, 1,1000);// 加速度配置
        check = 0x00;
        HAL_I2C_Mem_Write(&hi2c1,(*mpu).address,GYRO_CONFIG,1,&check, 1,1000);// 陀螺配置
        return 0;
    }
    return -1;
}