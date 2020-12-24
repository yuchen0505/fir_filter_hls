#include "fir.h"

void fir_filter (inp_data_t x,   coef_t c[N], out_data_t &y)
{

#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE s_axilite port=x
#pragma HLS INTERFACE s_axilite port=c
#pragma HLS INTERFACE s_axilite port=y

  static inp_data_t shift_reg[N];
#pragma HLS array_partition variable=shift_reg complete dim=1
  acc_t acc = 0;
  acc_t mult;

  Shift_Accum_Loop: for (int i=N-1;i>=0;i--)
  {
#pragma HLS LOOP_TRIPCOUNT min=1 max=16 avg=8
#pragma HLS PIPELINE II=1
#pragma HLS UNROLL

     if (i==0)
     {
       //acc+=x*c[0];
       shift_reg[0]=x;
     }
     else
     {
			shift_reg[i]=shift_reg[i-1];
     }
     mult = shift_reg[i]*c[i];
     acc  = acc + mult;

  }

  y = (out_data_t) acc;
}
