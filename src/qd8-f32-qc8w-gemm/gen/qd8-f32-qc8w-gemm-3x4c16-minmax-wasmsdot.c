// Auto-generated file. Do not edit!
//   Template: src/qs8-gemm/MRx4c16-wasmsdot.c.in
//   Generator: tools/xngen
//
// Copyright 2023 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>

#include <wasm_simd128.h>

#include <xnnpack/gemm.h>
#include <xnnpack/math.h>


void xnn_qd8_f32_qc8w_gemm_minmax_ukernel_3x4c16__wasmsdot(
    size_t mr,
    size_t nc,
    size_t kc,
    const int8_t* restrict a,
    size_t a_stride,
    const void* restrict w,
    float* restrict c,
    size_t cm_stride,
    size_t cn_stride,
    const union xnn_f32_minmax_params params[restrict XNN_MIN_ELEMENTS(1)],
    const struct xnn_qd8_quantization_params quantization_params[restrict XNN_MIN_ELEMENTS(1)]) XNN_OOB_READS
{
  assert(mr != 0);
  assert(mr <= 3);
  assert(nc != 0);
  assert(kc != 0);
  assert(kc % sizeof(int8_t) == 0);
  assert(a != NULL);
  assert(w != NULL);
  assert(c != NULL);

  kc = round_up_po2(kc, 16 * sizeof(int8_t));
  const int8_t* a0 = a;
  float* c0 = c;
  const struct xnn_qd8_quantization_params* qp0 = quantization_params;
  const int8_t* a1 = (const int8_t*) ((uintptr_t) a0 + a_stride);
  float* c1 = (float*) ((uintptr_t) c0 + cm_stride);
  const struct xnn_qd8_quantization_params* qp1 = &quantization_params[1];
  if XNN_UNPREDICTABLE(mr < 2) {
    a1 = a0;
    c1 = c0;
    qp1 = qp0;
  }
  const int8_t* a2 = (const int8_t*) ((uintptr_t) a1 + a_stride);
  float* c2 = (float*) ((uintptr_t) c1 + cm_stride);
  const struct xnn_qd8_quantization_params* qp2 = &quantization_params[2];
  if XNN_UNPREDICTABLE(mr <= 2) {
    a2 = a1;
    c2 = c1;
    qp2 = qp1;
  }

  do {
    v128_t vksum0 = wasm_v128_load32_zero(w);
    v128_t vksum1 = wasm_v128_load32_zero((const int32_t*) w + 1);
    v128_t vksum2 = wasm_v128_load32_zero((const int32_t*) w + 2);
    v128_t vksum3 = wasm_v128_load32_zero((const int32_t*) w + 3);
    const v128_t vinput_zero_point0 = wasm_v128_load32_splat(&qp0->zero_point);
    const v128_t vinput_zero_point1 = wasm_v128_load32_splat(&qp1->zero_point);
    const v128_t vinput_zero_point2 = wasm_v128_load32_splat(&qp2->zero_point);
    v128_t vacc0x0 = wasm_i32x4_mul(vksum0, vinput_zero_point0);
    v128_t vacc0x1 = wasm_i32x4_mul(vksum1, vinput_zero_point0);
    v128_t vacc0x2 = wasm_i32x4_mul(vksum2, vinput_zero_point0);
    v128_t vacc0x3 = wasm_i32x4_mul(vksum3, vinput_zero_point0);
    v128_t vacc1x0 = wasm_i32x4_mul(vksum0, vinput_zero_point1);
    v128_t vacc1x1 = wasm_i32x4_mul(vksum1, vinput_zero_point1);
    v128_t vacc1x2 = wasm_i32x4_mul(vksum2, vinput_zero_point1);
    v128_t vacc1x3 = wasm_i32x4_mul(vksum3, vinput_zero_point1);
    v128_t vacc2x0 = wasm_i32x4_mul(vksum0, vinput_zero_point2);
    v128_t vacc2x1 = wasm_i32x4_mul(vksum1, vinput_zero_point2);
    v128_t vacc2x2 = wasm_i32x4_mul(vksum2, vinput_zero_point2);
    v128_t vacc2x3 = wasm_i32x4_mul(vksum3, vinput_zero_point2);
    w = (const int32_t*) w + 4;

    size_t k = kc;
    do {
      const v128_t va0 = wasm_v128_load(a0);
      a0 += 16;
      const v128_t va1 = wasm_v128_load(a1);
      a1 += 16;
      const v128_t va2 = wasm_v128_load(a2);
      a2 += 16;

      const v128_t vb0 = wasm_v128_load(w);

      vacc0x0 = wasm_i32x4_relaxed_dot_i8x16_i7x16_add(va0, vb0, vacc0x0);
      vacc1x0 = wasm_i32x4_relaxed_dot_i8x16_i7x16_add(va1, vb0, vacc1x0);
      vacc2x0 = wasm_i32x4_relaxed_dot_i8x16_i7x16_add(va2, vb0, vacc2x0);
      const v128_t vb1 = wasm_v128_load((const int8_t*) w + 16);

      vacc0x1 = wasm_i32x4_relaxed_dot_i8x16_i7x16_add(va0, vb1, vacc0x1);
      vacc1x1 = wasm_i32x4_relaxed_dot_i8x16_i7x16_add(va1, vb1, vacc1x1);
      vacc2x1 = wasm_i32x4_relaxed_dot_i8x16_i7x16_add(va2, vb1, vacc2x1);
      const v128_t vb2 = wasm_v128_load((const int8_t*) w + 32);

      vacc0x2 = wasm_i32x4_relaxed_dot_i8x16_i7x16_add(va0, vb2, vacc0x2);
      vacc1x2 = wasm_i32x4_relaxed_dot_i8x16_i7x16_add(va1, vb2, vacc1x2);
      vacc2x2 = wasm_i32x4_relaxed_dot_i8x16_i7x16_add(va2, vb2, vacc2x2);
      const v128_t vb3 = wasm_v128_load((const int8_t*) w + 48);

      vacc0x3 = wasm_i32x4_relaxed_dot_i8x16_i7x16_add(va0, vb3, vacc0x3);
      vacc1x3 = wasm_i32x4_relaxed_dot_i8x16_i7x16_add(va1, vb3, vacc1x3);
      vacc2x3 = wasm_i32x4_relaxed_dot_i8x16_i7x16_add(va2, vb3, vacc2x3);

      w = (const int8_t*) w + 64;
      k -= 16 * sizeof(int8_t);
    } while (k != 0);

    const v128_t vacc0x02 = wasm_i32x4_add(wasm_v32x4_shuffle(vacc0x0, vacc0x2, 0, 4, 1, 5), wasm_v32x4_shuffle(vacc0x0, vacc0x2, 2, 6, 3, 7));
    const v128_t vacc0x13 = wasm_i32x4_add(wasm_v32x4_shuffle(vacc0x1, vacc0x3, 0, 4, 1, 5), wasm_v32x4_shuffle(vacc0x1, vacc0x3, 2, 6, 3, 7));
    const v128_t vacc1x02 = wasm_i32x4_add(wasm_v32x4_shuffle(vacc1x0, vacc1x2, 0, 4, 1, 5), wasm_v32x4_shuffle(vacc1x0, vacc1x2, 2, 6, 3, 7));
    const v128_t vacc1x13 = wasm_i32x4_add(wasm_v32x4_shuffle(vacc1x1, vacc1x3, 0, 4, 1, 5), wasm_v32x4_shuffle(vacc1x1, vacc1x3, 2, 6, 3, 7));
    const v128_t vacc2x02 = wasm_i32x4_add(wasm_v32x4_shuffle(vacc2x0, vacc2x2, 0, 4, 1, 5), wasm_v32x4_shuffle(vacc2x0, vacc2x2, 2, 6, 3, 7));
    const v128_t vacc2x13 = wasm_i32x4_add(wasm_v32x4_shuffle(vacc2x1, vacc2x3, 0, 4, 1, 5), wasm_v32x4_shuffle(vacc2x1, vacc2x3, 2, 6, 3, 7));

    v128_t vacc0x0123 = wasm_i32x4_add(wasm_v32x4_shuffle(vacc0x02, vacc0x13, 0, 4, 1, 5), wasm_v32x4_shuffle(vacc0x02, vacc0x13, 2, 6, 3, 7));
    v128_t vacc1x0123 = wasm_i32x4_add(wasm_v32x4_shuffle(vacc1x02, vacc1x13, 0, 4, 1, 5), wasm_v32x4_shuffle(vacc1x02, vacc1x13, 2, 6, 3, 7));
    v128_t vacc2x0123 = wasm_i32x4_add(wasm_v32x4_shuffle(vacc2x02, vacc2x13, 0, 4, 1, 5), wasm_v32x4_shuffle(vacc2x02, vacc2x13, 2, 6, 3, 7));

    vacc0x0123 = wasm_f32x4_convert_i32x4(vacc0x0123);
    vacc1x0123 = wasm_f32x4_convert_i32x4(vacc1x0123);
    vacc2x0123 = wasm_f32x4_convert_i32x4(vacc2x0123);

    const v128_t vinput_scale0 = wasm_v128_load32_splat(&qp0->inv_scale);
    const v128_t vinput_scale1 = wasm_v128_load32_splat(&qp1->inv_scale);
    const v128_t vinput_scale2 = wasm_v128_load32_splat(&qp2->inv_scale);

    vacc0x0123 = wasm_f32x4_mul(vacc0x0123, vinput_scale0);
    vacc1x0123 = wasm_f32x4_mul(vacc1x0123, vinput_scale1);
    vacc2x0123 = wasm_f32x4_mul(vacc2x0123, vinput_scale2);

    const v128_t vfilter_output_scale0123 = wasm_v128_load(w);
    vacc0x0123 = wasm_f32x4_mul(vacc0x0123, vfilter_output_scale0123);
    vacc1x0123 = wasm_f32x4_mul(vacc1x0123, vfilter_output_scale0123);
    vacc2x0123 = wasm_f32x4_mul(vacc2x0123, vfilter_output_scale0123);
    w = (const float*) w + 4;

    const v128_t vbias0123 = wasm_v128_load(w);
    vacc0x0123 = wasm_f32x4_add(vacc0x0123, vbias0123);
    vacc1x0123 = wasm_f32x4_add(vacc1x0123, vbias0123);
    vacc2x0123 = wasm_f32x4_add(vacc2x0123, vbias0123);
    w = (const float*) w + 4;

    const v128_t vmin = wasm_v128_load64_splat(params->wasmsimd.min);
    vacc0x0123 = wasm_f32x4_pmax(vacc0x0123, vmin);
    vacc1x0123 = wasm_f32x4_pmax(vacc1x0123, vmin);
    vacc2x0123 = wasm_f32x4_pmax(vacc2x0123, vmin);

    const v128_t vmax = wasm_v128_load64_splat(params->wasmsimd.max);
    vacc0x0123 = wasm_f32x4_pmin(vacc0x0123, vmax);
    vacc1x0123 = wasm_f32x4_pmin(vacc1x0123, vmax);
    vacc2x0123 = wasm_f32x4_pmin(vacc2x0123, vmax);

    if XNN_LIKELY(nc >= 4) {
      wasm_v128_store(c0, vacc0x0123);
      wasm_v128_store(c1, vacc1x0123);
      wasm_v128_store(c2, vacc2x0123);

      a0 = (const int8_t*) ((uintptr_t) a0 - kc);
      a1 = (const int8_t*) ((uintptr_t) a1 - kc);
      a2 = (const int8_t*) ((uintptr_t) a2 - kc);

      c0 = (float*) ((uintptr_t) c0 + cn_stride);
      c1 = (float*) ((uintptr_t) c1 + cn_stride);
      c2 = (float*) ((uintptr_t) c2 + cn_stride);

      nc -= 4;
    } else {
      if (nc & 2) {
        wasm_v128_store64_lane(c0, vacc0x0123, 0);
        vacc0x0123 = wasm_v64x2_shuffle(vacc0x0123, vacc0x0123, 1, 1);
        c0 += 2;
        wasm_v128_store64_lane(c1, vacc1x0123, 0);
        vacc1x0123 = wasm_v64x2_shuffle(vacc1x0123, vacc1x0123, 1, 1);
        c1 += 2;
        wasm_v128_store64_lane(c2, vacc2x0123, 0);
        vacc2x0123 = wasm_v64x2_shuffle(vacc2x0123, vacc2x0123, 1, 1);
        c2 += 2;
      }
      if (nc & 1) {
        wasm_v128_store32_lane(c0, vacc0x0123, 0);
        wasm_v128_store32_lane(c1, vacc1x0123, 0);
        wasm_v128_store32_lane(c2, vacc2x0123, 0);
      }
      nc = 0;
    }
  } while (nc != 0);
}
