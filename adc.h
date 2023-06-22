#ifndef __ADC
    #define __ADC

    void ADC_Init(unsigned short channel);
    unsigned int ADC_Read(unsigned short channel);
#endif