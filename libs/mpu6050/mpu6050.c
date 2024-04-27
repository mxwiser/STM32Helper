//
// Created by neowa on 2024/4/27.
//

#include "mpu6050.h"
#include "math.h"
extern  I2C_HandleTypeDef hi2c1;

void send_cmd(uint16_t cmd,uint8_t data){
    HAL_I2C_Mem_Write(&hi2c1,MPU6050_ADDR,cmd,1,&data, 1,1000);
}

int mpu6050_Init(){
    uint8_t check;
    HAL_I2C_Mem_Read(&hi2c1,MPU6050_ADDR,WHO_AM_I,1,&check,1,1000);
    if (check==0x68){
        send_cmd(PWR_MGMT_1,0x00);//唤醒
        send_cmd(SMPLRT_DIV,0x19);//速率
        send_cmd(ACCEL_CONFIG,0x00);//加速度配置
        send_cmd(GYRO_CONFIG,0x00);//陀螺配置
        send_cmd(MPU_INT_EN_REG,0x01);//开启中断
        send_cmd(MPU_INTBP_CFG_REG,0X9c);//高电平触发
        return 0;
    }
    return -1;
}
int16_t get_origin_data(uint8_t address)
{
    uint8_t  Data_H,Data_L;
    uint16_t data;
    HAL_I2C_Mem_Read(&hi2c1,MPU6050_ADDR,address,1,&Data_H,1,1000);
    HAL_I2C_Mem_Read(&hi2c1,MPU6050_ADDR,address+1,1,&Data_L,1,1000);
    data = Data_H;
    data = (data << 8) | Data_L;  // 合成数据
    return data;
}
void get_ACCEL(mpu6050_t *mpu){
    mpu->accel_x= get_origin_data(ACCEL_XOUT_H)/16384.0;
    mpu->accel_y= get_origin_data(ACCEL_YOUT_H)/16384.0;
    mpu->accel_z= get_origin_data(ACCEL_ZOUT_H)/16384.0;
}
void get_GYRO(mpu6050_t *mpu){
    mpu->gyro_x= get_origin_data(GYRO_XOUT_H)/131*dT;
    mpu->gyro_y= get_origin_data(GYRO_YOUT_H)/131*dT;
    mpu->gyro_z= get_origin_data(GYRO_ZOUT_H)/131*dT;
}

void updateAngle(mpu6050_t *mpu){
   float d= sqrtf(mpu->accel_x*mpu->accel_x+mpu->accel_y*mpu->accel_y+mpu->accel_z*mpu->accel_z);
   mpu->angle_x= acosf(mpu->accel_x/d)*57.29577*Q_FILTER + (1-Q_FILTER)*mpu->angle_x -mpu->gyro_x;
   mpu->angle_y= acosf(mpu->accel_y/d)*57.29577*Q_FILTER + (1-Q_FILTER)*mpu->angle_y -mpu->gyro_y;
   mpu->angle_z= acosf(mpu->accel_z/d)*57.29577*Q_FILTER + (1-Q_FILTER)*mpu->angle_z -mpu->gyro_z;
}

void getMpu6050Temp(mpu6050_t *mpu){
    mpu->temp= get_origin_data(TEMP_OUT_H);
}