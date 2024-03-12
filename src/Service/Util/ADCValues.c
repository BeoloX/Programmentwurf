#include "ADCModule.h"
#include "Util/Filter/Filter.h"


EMAFilterData_t Input_Pot1;
EMAFilterData_t Input_Pot2;


void initFilters(){

	 filterInitEMA(&Input_Pot1, 10, 5, false);
	 filterInitEMA(&Input_Pot2, 10, 5, false);
}


int32_t filteredChannel1(){

	int32_t adcMicroVoltValue=adcReadChannel(ADC_INPUT0);

	int32_t filteredValue = filterEMA(&Input_Pot1, adcMicroVoltValue);

	return filteredValue;

}

int32_t filteredChannel2(){

	int32_t adcMicroVoltValue=adcReadChannel(ADC_INPUT1);

	int32_t filteredValue = filterEMA(&Input_Pot2, adcMicroVoltValue);

	return filteredValue;

}

