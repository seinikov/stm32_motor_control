#include "main.h"
#include "bsp_cordic.h"

void CORDICx_Config(CORDIC_TypeDef *CORDICx){
    LL_CORDIC_Config(CORDICx,
                    LL_CORDIC_FUNCTION_SINE,
                    LL_CORDIC_PRECISION_6CYCLES,
                    LL_CORDIC_SCALE_0,
                    LL_CORDIC_NBWRITE_1,
                    LL_CORDIC_NBREAD_1,
                    LL_CORDIC_INSIZE_32BITS,
                    LL_CORDIC_OUTSIZE_32BITS
    );
}
