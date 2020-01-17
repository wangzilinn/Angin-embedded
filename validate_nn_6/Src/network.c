/**
  ******************************************************************************
  * @file    network.c
  * @author  AST Embedded Analytics Research Platform
  * @date    Thu Jan 16 11:27:39 2020
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2018 STMicroelectronics.
  * All rights reserved.
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */


#include "network.h"

#include "ai_platform_interface.h"
#include "ai_math_helpers.h"

#include "core_common.h"
#include "layers.h"

#undef AI_TOOLS_VERSION_MAJOR
#undef AI_TOOLS_VERSION_MINOR
#undef AI_TOOLS_VERSION_MICRO
#define AI_TOOLS_VERSION_MAJOR 5
#define AI_TOOLS_VERSION_MINOR 0
#define AI_TOOLS_VERSION_MICRO 0


#undef AI_TOOLS_API_VERSION_MAJOR
#undef AI_TOOLS_API_VERSION_MINOR
#undef AI_TOOLS_API_VERSION_MICRO
#define AI_TOOLS_API_VERSION_MAJOR 1
#define AI_TOOLS_API_VERSION_MINOR 3
#define AI_TOOLS_API_VERSION_MICRO 0

#undef AI_NET_OBJ_INSTANCE
#define AI_NET_OBJ_INSTANCE g_network
 
#undef AI_NETWORK_MODEL_SIGNATURE
#define AI_NETWORK_MODEL_SIGNATURE     "0c4409ac77edf66cabac2e5ec04b2e65"

#ifndef AI_TOOLS_REVISION_ID
#define AI_TOOLS_REVISION_ID     "(rev-5.0.0)"
#endif

#undef AI_TOOLS_DATE_TIME
#define AI_TOOLS_DATE_TIME   "Thu Jan 16 11:27:39 2020"

#undef AI_TOOLS_COMPILE_TIME
#define AI_TOOLS_COMPILE_TIME    __DATE__ " " __TIME__

#undef AI_NETWORK_N_BATCHES
#define AI_NETWORK_N_BATCHES         (1)

/**  Forward network declaration section  *************************************/
AI_STATIC ai_network AI_NET_OBJ_INSTANCE;


/**  Forward network array declarations  **************************************/
AI_STATIC ai_array conv2d_12_scratch0_array;   /* Array #0 */
AI_STATIC ai_array conv2d_11_scratch0_array;   /* Array #1 */
AI_STATIC ai_array dense_12_bias_array;   /* Array #2 */
AI_STATIC ai_array dense_12_weights_array;   /* Array #3 */
AI_STATIC ai_array dense_11_bias_array;   /* Array #4 */
AI_STATIC ai_array dense_11_weights_array;   /* Array #5 */
AI_STATIC ai_array conv2d_12_bias_array;   /* Array #6 */
AI_STATIC ai_array conv2d_12_weights_array;   /* Array #7 */
AI_STATIC ai_array conv2d_11_bias_array;   /* Array #8 */
AI_STATIC ai_array conv2d_11_weights_array;   /* Array #9 */
AI_STATIC ai_array input_0_output_array;   /* Array #10 */
AI_STATIC ai_array conv2d_11_output_array;   /* Array #11 */
AI_STATIC ai_array conv2d_12_output_array;   /* Array #12 */
AI_STATIC ai_array dense_11_output_array;   /* Array #13 */
AI_STATIC ai_array dense_11_nl_output_array;   /* Array #14 */
AI_STATIC ai_array dense_12_output_array;   /* Array #15 */
AI_STATIC ai_array dense_12_nl_output_array;   /* Array #16 */


/**  Forward network tensor declarations  *************************************/
AI_STATIC ai_tensor conv2d_12_scratch0;   /* Tensor #0 */
AI_STATIC ai_tensor conv2d_11_scratch0;   /* Tensor #1 */
AI_STATIC ai_tensor dense_12_bias;   /* Tensor #2 */
AI_STATIC ai_tensor dense_12_weights;   /* Tensor #3 */
AI_STATIC ai_tensor dense_11_bias;   /* Tensor #4 */
AI_STATIC ai_tensor dense_11_weights;   /* Tensor #5 */
AI_STATIC ai_tensor conv2d_12_bias;   /* Tensor #6 */
AI_STATIC ai_tensor conv2d_12_weights;   /* Tensor #7 */
AI_STATIC ai_tensor conv2d_11_bias;   /* Tensor #8 */
AI_STATIC ai_tensor conv2d_11_weights;   /* Tensor #9 */
AI_STATIC ai_tensor input_0_output;   /* Tensor #10 */
AI_STATIC ai_tensor conv2d_11_output;   /* Tensor #11 */
AI_STATIC ai_tensor conv2d_12_output;   /* Tensor #12 */
AI_STATIC ai_tensor conv2d_12_output0;   /* Tensor #13 */
AI_STATIC ai_tensor dense_11_output;   /* Tensor #14 */
AI_STATIC ai_tensor dense_11_nl_output;   /* Tensor #15 */
AI_STATIC ai_tensor dense_12_output;   /* Tensor #16 */
AI_STATIC ai_tensor dense_12_nl_output;   /* Tensor #17 */


/**  Forward network tensor chain declarations  *******************************/
AI_STATIC_CONST ai_tensor_chain conv2d_11_chain;   /* Chain #0 */
AI_STATIC_CONST ai_tensor_chain conv2d_12_chain;   /* Chain #1 */
AI_STATIC_CONST ai_tensor_chain dense_11_chain;   /* Chain #2 */
AI_STATIC_CONST ai_tensor_chain dense_11_nl_chain;   /* Chain #3 */
AI_STATIC_CONST ai_tensor_chain dense_12_chain;   /* Chain #4 */
AI_STATIC_CONST ai_tensor_chain dense_12_nl_chain;   /* Chain #5 */


/**  Forward network layer declarations  **************************************/
AI_STATIC ai_layer_conv2d_nl_pool conv2d_11_layer; /* Layer #0 */
AI_STATIC ai_layer_conv2d_nl_pool conv2d_12_layer; /* Layer #1 */
AI_STATIC ai_layer_dense dense_11_layer; /* Layer #2 */
AI_STATIC ai_layer_nl dense_11_nl_layer; /* Layer #3 */
AI_STATIC ai_layer_dense dense_12_layer; /* Layer #4 */
AI_STATIC ai_layer_nl dense_12_nl_layer; /* Layer #5 */


/**  Array declarations section  **********************************************/
AI_ARRAY_OBJ_DECLARE(
    conv2d_12_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 416,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    conv2d_11_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 960,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    dense_12_bias_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 3,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    dense_12_weights_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 27,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    dense_11_bias_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 9,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    dense_11_weights_array, AI_ARRAY_FORMAT_LUT8_FLOAT,
    NULL, NULL, 5184,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    conv2d_12_bias_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 16,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    conv2d_12_weights_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 2304,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    conv2d_11_bias_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 16,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    conv2d_11_weights_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 144,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    input_0_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
    NULL, NULL, 960,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    conv2d_11_output_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 3360,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    conv2d_12_output_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 576,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    dense_11_output_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 9,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    dense_11_nl_output_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 9,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    dense_12_output_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 3,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    dense_12_nl_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
    NULL, NULL, 3,
     AI_STATIC)




/**  Tensor declarations section  *********************************************/
AI_TENSOR_OBJ_DECLARE(
  conv2d_12_scratch0, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 16, 13, 2), AI_STRIDE_INIT(4, 4, 4, 64, 832),
  1, &conv2d_12_scratch0_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  conv2d_11_scratch0, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 16, 30, 2), AI_STRIDE_INIT(4, 4, 4, 64, 1920),
  1, &conv2d_11_scratch0_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  dense_12_bias, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 3, 1, 1), AI_STRIDE_INIT(4, 4, 4, 12, 12),
  1, &dense_12_bias_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  dense_12_weights, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 9, 3, 1, 1), AI_STRIDE_INIT(4, 4, 36, 108, 108),
  1, &dense_12_weights_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  dense_11_bias, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 9, 1, 1), AI_STRIDE_INIT(4, 4, 4, 36, 36),
  1, &dense_11_bias_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  dense_11_weights, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 576, 9, 1, 1), AI_STRIDE_INIT(4, 1, 576, 5184, 5184),
  1, &dense_11_weights_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  conv2d_12_bias, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 16, 1, 1), AI_STRIDE_INIT(4, 4, 4, 64, 64),
  1, &conv2d_12_bias_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  conv2d_12_weights, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 16, 3, 3, 16), AI_STRIDE_INIT(4, 4, 64, 192, 576),
  1, &conv2d_12_weights_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  conv2d_11_bias, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 16, 1, 1), AI_STRIDE_INIT(4, 4, 4, 64, 64),
  1, &conv2d_11_bias_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  conv2d_11_weights, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 3, 3, 16), AI_STRIDE_INIT(4, 4, 4, 12, 36),
  1, &conv2d_11_weights_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  input_0_output, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 1, 32, 30), AI_STRIDE_INIT(4, 4, 4, 4, 128),
  1, &input_0_output_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  conv2d_11_output, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 16, 15, 14), AI_STRIDE_INIT(4, 4, 4, 64, 960),
  1, &conv2d_11_output_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  conv2d_12_output, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 16, 6, 6), AI_STRIDE_INIT(4, 4, 4, 64, 384),
  1, &conv2d_12_output_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  conv2d_12_output0, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 576, 1, 1), AI_STRIDE_INIT(4, 4, 4, 2304, 2304),
  1, &conv2d_12_output_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  dense_11_output, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 9, 1, 1), AI_STRIDE_INIT(4, 4, 4, 36, 36),
  1, &dense_11_output_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  dense_11_nl_output, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 9, 1, 1), AI_STRIDE_INIT(4, 4, 4, 36, 36),
  1, &dense_11_nl_output_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  dense_12_output, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 3, 1, 1), AI_STRIDE_INIT(4, 4, 4, 12, 12),
  1, &dense_12_output_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  dense_12_nl_output, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 3, 1, 1), AI_STRIDE_INIT(4, 4, 4, 12, 12),
  1, &dense_12_nl_output_array, NULL)


/**  Layer declarations section  **********************************************/


AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_11_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_ENTRY(&input_0_output),
  AI_TENSOR_LIST_ENTRY(&conv2d_11_output),
  AI_TENSOR_LIST_ENTRY(&conv2d_11_weights, &conv2d_11_bias, NULL),
  AI_TENSOR_LIST_ENTRY(&conv2d_11_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  conv2d_11_layer, 0,
  OPTIMIZED_CONV2D_TYPE,
  conv2d_nl_pool, forward_conv2d_nl_pool,
  &AI_NET_OBJ_INSTANCE, &conv2d_12_layer, AI_STATIC,
  .tensors = &conv2d_11_chain, 
  .groups = 1, 
  .nl_func = nl_func_relu_array_f32, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_size = AI_SHAPE_2D_INIT(2, 2), 
  .pool_stride = AI_SHAPE_2D_INIT(2, 2), 
  .pool_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_func = pool_func_mp_array_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_12_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_ENTRY(&conv2d_11_output),
  AI_TENSOR_LIST_ENTRY(&conv2d_12_output),
  AI_TENSOR_LIST_ENTRY(&conv2d_12_weights, &conv2d_12_bias, NULL),
  AI_TENSOR_LIST_ENTRY(&conv2d_12_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  conv2d_12_layer, 3,
  OPTIMIZED_CONV2D_TYPE,
  conv2d_nl_pool, forward_conv2d_nl_pool,
  &AI_NET_OBJ_INSTANCE, &dense_11_layer, AI_STATIC,
  .tensors = &conv2d_12_chain, 
  .groups = 1, 
  .nl_func = nl_func_relu_array_f32, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_size = AI_SHAPE_2D_INIT(2, 2), 
  .pool_stride = AI_SHAPE_2D_INIT(2, 2), 
  .pool_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_func = pool_func_mp_array_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_11_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_ENTRY(&conv2d_12_output0),
  AI_TENSOR_LIST_ENTRY(&dense_11_output),
  AI_TENSOR_LIST_ENTRY(&dense_11_weights, &dense_11_bias),
  AI_TENSOR_LIST_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_11_layer, 7,
  DENSE_TYPE,
  dense, forward_dense,
  &AI_NET_OBJ_INSTANCE, &dense_11_nl_layer, AI_STATIC,
  .tensors = &dense_11_chain, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_11_nl_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_ENTRY(&dense_11_output),
  AI_TENSOR_LIST_ENTRY(&dense_11_nl_output),
  AI_TENSOR_LIST_EMPTY,
  AI_TENSOR_LIST_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_11_nl_layer, 7,
  NL_TYPE,
  nl, forward_relu,
  &AI_NET_OBJ_INSTANCE, &dense_12_layer, AI_STATIC,
  .tensors = &dense_11_nl_chain, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_12_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_ENTRY(&dense_11_nl_output),
  AI_TENSOR_LIST_ENTRY(&dense_12_output),
  AI_TENSOR_LIST_ENTRY(&dense_12_weights, &dense_12_bias),
  AI_TENSOR_LIST_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_12_layer, 9,
  DENSE_TYPE,
  dense, forward_dense,
  &AI_NET_OBJ_INSTANCE, &dense_12_nl_layer, AI_STATIC,
  .tensors = &dense_12_chain, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_12_nl_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_ENTRY(&dense_12_output),
  AI_TENSOR_LIST_ENTRY(&dense_12_nl_output),
  AI_TENSOR_LIST_EMPTY,
  AI_TENSOR_LIST_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_12_nl_layer, 9,
  NL_TYPE,
  nl, forward_sm,
  &AI_NET_OBJ_INSTANCE, &dense_12_nl_layer, AI_STATIC,
  .tensors = &dense_12_nl_chain, 
)


AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_OBJ_INIT(AI_BUFFER_FORMAT_U8,
                     1, 1, 16284, 1,
                     NULL),
  AI_BUFFER_OBJ_INIT(AI_BUFFER_FORMAT_U8,
                     1, 1, 17408, 1,
                     NULL),
  AI_TENSOR_LIST_IO_ENTRY(AI_FLAG_NONE, AI_NETWORK_IN_NUM, &input_0_output),
  AI_TENSOR_LIST_IO_ENTRY(AI_FLAG_NONE, AI_NETWORK_OUT_NUM, &dense_12_nl_output),
  &conv2d_11_layer, 0, NULL)



AI_DECLARE_STATIC
ai_bool network_configure_activations(
  ai_network* net_ctx, const ai_buffer* activation_buffer)
{
  AI_ASSERT(net_ctx &&  activation_buffer && activation_buffer->data)

  ai_ptr activations = AI_PTR(AI_PTR_ALIGN(activation_buffer->data, 4));
  AI_ASSERT(activations)
  AI_UNUSED(net_ctx)

  {
    /* Updating activations (byte) offsets */
    conv2d_12_scratch0_array.data = AI_PTR(activations + 0);
    conv2d_12_scratch0_array.data_start = AI_PTR(activations + 0);
    conv2d_11_scratch0_array.data = AI_PTR(activations + 0);
    conv2d_11_scratch0_array.data_start = AI_PTR(activations + 0);
    input_0_output_array.data = AI_PTR(NULL);
    input_0_output_array.data_start = AI_PTR(NULL);
    conv2d_11_output_array.data = AI_PTR(activations + 3968);
    conv2d_11_output_array.data_start = AI_PTR(activations + 3968);
    conv2d_12_output_array.data = AI_PTR(activations + 1664);
    conv2d_12_output_array.data_start = AI_PTR(activations + 1664);
    dense_11_output_array.data = AI_PTR(activations + 0);
    dense_11_output_array.data_start = AI_PTR(activations + 0);
    dense_11_nl_output_array.data = AI_PTR(activations + 0);
    dense_11_nl_output_array.data_start = AI_PTR(activations + 0);
    dense_12_output_array.data = AI_PTR(activations + 36);
    dense_12_output_array.data_start = AI_PTR(activations + 36);
    dense_12_nl_output_array.data = AI_PTR(NULL);
    dense_12_nl_output_array.data_start = AI_PTR(NULL);
    
  }
  return true;
}



AI_DECLARE_STATIC
ai_bool network_configure_weights(
  ai_network* net_ctx, const ai_buffer* weights_buffer)
{
  AI_ASSERT(net_ctx &&  weights_buffer && weights_buffer->data)

  ai_ptr weights = AI_PTR(weights_buffer->data);
  AI_ASSERT(weights)
  AI_UNUSED(net_ctx)

  {
    /* Updating weights (byte) offsets */
    
    dense_12_bias_array.format |= AI_FMT_FLAG_CONST;
    dense_12_bias_array.data = AI_PTR(weights + 16272);
    dense_12_bias_array.data_start = AI_PTR(weights + 16272);
    dense_12_weights_array.format |= AI_FMT_FLAG_CONST;
    dense_12_weights_array.data = AI_PTR(weights + 16164);
    dense_12_weights_array.data_start = AI_PTR(weights + 16164);
    dense_11_bias_array.format |= AI_FMT_FLAG_CONST;
    dense_11_bias_array.data = AI_PTR(weights + 16128);
    dense_11_bias_array.data_start = AI_PTR(weights + 16128);
    dense_11_weights_array.format |= AI_FMT_FLAG_CONST;
    dense_11_weights_array.data = AI_PTR(weights + 10944);
    dense_11_weights_array.data_start = AI_PTR(weights + 9920);
    conv2d_12_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_12_bias_array.data = AI_PTR(weights + 9856);
    conv2d_12_bias_array.data_start = AI_PTR(weights + 9856);
    conv2d_12_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_12_weights_array.data = AI_PTR(weights + 640);
    conv2d_12_weights_array.data_start = AI_PTR(weights + 640);
    conv2d_11_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_11_bias_array.data = AI_PTR(weights + 576);
    conv2d_11_bias_array.data_start = AI_PTR(weights + 576);
    conv2d_11_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_11_weights_array.data = AI_PTR(weights + 0);
    conv2d_11_weights_array.data_start = AI_PTR(weights + 0);
  }

  return true;
}


/**  PUBLIC APIs SECTION  *****************************************************/

AI_API_ENTRY
ai_bool ai_network_get_info(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if ( report && net_ctx )
  {
    ai_network_report r = {
      .model_name        = AI_NETWORK_MODEL_NAME,
      .model_signature   = AI_NETWORK_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = {AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR,
                            AI_TOOLS_API_VERSION_MICRO, 0x0},

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 517361,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .activations       = AI_STRUCT_INIT,
      .params            = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x0,
    };

    if ( !ai_platform_api_get_network_report(network, &r) ) return false;

    *report = r;
    return true;
  }

  return false;
}

AI_API_ENTRY
ai_error ai_network_get_error(ai_handle network)
{
  return ai_platform_network_get_error(network);
}

AI_API_ENTRY
ai_error ai_network_create(
  ai_handle* network, const ai_buffer* network_config)
{
  return ai_platform_network_create(
    network, network_config, 
    &AI_NET_OBJ_INSTANCE,
    AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR, AI_TOOLS_API_VERSION_MICRO);
}

AI_API_ENTRY
ai_handle ai_network_destroy(ai_handle network)
{
  return ai_platform_network_destroy(network);
}

AI_API_ENTRY
ai_bool ai_network_init(
  ai_handle network, const ai_network_params* params)
{
  ai_network* net_ctx = ai_platform_network_init(network, params);
  if ( !net_ctx ) return false;

  ai_bool ok = true;
  ok &= network_configure_weights(net_ctx, &params->params);
  ok &= network_configure_activations(net_ctx, &params->activations);

  return ok;
}


AI_API_ENTRY
ai_i32 ai_network_run(
  ai_handle network, const ai_buffer* input, ai_buffer* output)
{
  return ai_platform_network_process(network, input, output);
}

AI_API_ENTRY
ai_i32 ai_network_forward(ai_handle network, const ai_buffer* input)
{
  return ai_platform_network_process(network, input, NULL);
}

#undef AI_NETWORK_MODEL_SIGNATURE
#undef AI_NET_OBJ_INSTANCE
#undef AI_TOOLS_VERSION_MAJOR
#undef AI_TOOLS_VERSION_MINOR
#undef AI_TOOLS_VERSION_MICRO
#undef AI_TOOLS_API_VERSION_MAJOR
#undef AI_TOOLS_API_VERSION_MINOR
#undef AI_TOOLS_API_VERSION_MICRO
#undef AI_TOOLS_DATE_TIME
#undef AI_TOOLS_COMPILE_TIME

