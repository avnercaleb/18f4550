#ifndef __SPI
    #define __SPI

    #include "mcu.h"
    #include <xc.h>

    typedef enum {
        spi_master_osc_div4 = 0b00100000,
        spi_master_osc_div16 = 0b00100001,
        spi_master_osc_div64 = 0b00100010,
        spi_master_tmr2 = 0b00100011,
        spi_slave_ss_en = 0b00100100,
        spi_slave_ss_dis = 0b00100101 
    }Spi_Type;
    
    typedef enum {
        spi_clock_high = 0b00010000,
        spi_clock_low = 0b00000000
    }Spi_Clock_Idle;
    
    typedef enum {
        spi_data_sample_middle = 0b00000000,
        spi_data_sample_end = 0b10000000
    }Spi_Data_Sample;
    
    typedef enum {
        spi_low_to_high = 0b00000000,
        spi_high_to_low = 0b01000000
    }Spi_Transmit_Edge;
    
    void Spi_Init(Spi_Type, Spi_Clock_Idle, Spi_Data_Sample, Spi_Transmit_Edge);
    void Spi_Write(uint8_t);
    unsigned SpiDataReady();
    SpiReceiveWait();
    uint8_t Spi_Read();
#endif