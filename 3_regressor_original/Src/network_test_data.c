#include "network_test_data.h"

ai_handle ai_network_test_data_weights_get(void)
{

  AI_ALIGNED(4)
  static const ai_u8 s_network_test_weights[ 8 ] = {
    0x5d, 0x46, 0xbd, 0x3e, 0x82, 0x1d, 0x00, 0x40
  };

  return AI_HANDLE_PTR(s_network_test_weights);

}

