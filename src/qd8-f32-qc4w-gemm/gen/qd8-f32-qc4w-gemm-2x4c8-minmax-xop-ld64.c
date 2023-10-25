// Auto-generated file. Do not edit!
//   Template: src/qs8-gemm/MRx4c8-sse.c.in
//   Generator: tools/xngen
//
// Copyright 2020 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>

#ifdef _MSC_VER
  #include <intrin.h>
#else
  #include <x86intrin.h>
#endif

#include <xnnpack/gemm.h>
#include <xnnpack/math.h>
#include <xnnpack/unaligned.h>


void xnn_qd8_f32_qc4w_gemm_minmax_ukernel_2x4c8__xop_ld64(
    size_t mr,
    size_t nc,
    size_t kc,
    const int8_t* restrict a,
    size_t a_stride,
    const void* restrict w,
    float* restrict c,
    size_t cm_stride,
    size_t cn_stride,
    const union xnn_f32_qc4w_minmax_params params[restrict XNN_MIN_ELEMENTS(1)],
    const struct xnn_qd8_quantization_params quantization_params[restrict XNN_MIN_ELEMENTS(1)]) XNN_OOB_READS
{
  assert(mr != 0);
  assert(mr <= 2);
  assert(nc != 0);
  assert(kc != 0);
  assert(kc % sizeof(int8_t) == 0);
  assert(a != NULL);
  assert(w != NULL);
  assert(c != NULL);

  kc = round_up_po2(kc, 8 * sizeof(int8_t));
  const int8_t* a0 = a;
  float* c0 = c;
  const int8_t* a1 = (const int8_t*) ((uintptr_t) a0 + a_stride);
  float* c1 = (float*) ((uintptr_t) c0 + cm_stride);
  if XNN_UNPREDICTABLE(mr != 2) {
    a1 = a0;
    c1 = c0;
  }

  const __m128i vmask = _mm_load_si128((const __m128i*) params->xop.mask);  // 0xF0
  const __m128i vshift = _mm_load_si128((const __m128i*) params->xop.shift);  // 4
  const __m128i vpermlo = _mm_load_si128((const __m128i*) params->xop.permlo);
  do {
    const __m128i vksum = _mm_load_si128((const __m128i*) w);
    const __m128i vinput_zero_point0 = _mm_castps_si128(_mm_broadcast_ss((const float*) &quantization_params[0].zero_point));
    const __m128i vinput_zero_point1 = _mm_castps_si128(_mm_broadcast_ss((const float*) &quantization_params[1].zero_point));
    const __m128i vzero = _mm_setzero_si128();
    const __m128i vinit0 = _mm_mullo_epi32(vksum, vinput_zero_point0);
    const __m128i vinit1 = _mm_mullo_epi32(vksum, vinput_zero_point1);
    __m128i vacc0x0 = _mm_blend_epi16(vinit0, vzero, 0xFC);
    __m128i vacc0x1 = _mm_blend_epi16(vinit0, vzero, 0xF3);
    __m128i vacc0x2 = _mm_blend_epi16(vinit0, vzero, 0xCF);
    __m128i vacc0x3 = _mm_blend_epi16(vinit0, vzero, 0x3F);
    __m128i vacc1x0 = _mm_blend_epi16(vinit1, vzero, 0xFC);
    __m128i vacc1x1 = _mm_blend_epi16(vinit1, vzero, 0xF3);
    __m128i vacc1x2 = _mm_blend_epi16(vinit1, vzero, 0xCF);
    __m128i vacc1x3 = _mm_blend_epi16(vinit1, vzero, 0x3F);
    w = (const int32_t*) w + 4;

    size_t k = kc;
    while (k >= 8 * sizeof(int8_t)) {
      const __m128i va0 = _mm_loadl_epi64((const __m128i*) a0);
      const __m128i vxa0 = _mm_cvtepi8_epi16(va0);
      a0 += 8;
      const __m128i va1 = _mm_loadl_epi64((const __m128i*) a1);
      const __m128i vxa1 = _mm_cvtepi8_epi16(va1);
      a1 += 8;

      const __m128i vb0 = _mm_cvtsi32_si128((int) unaligned_load_u32((const int8_t*) w));
      const __m128i vbl0 = _mm_shl_epi8(vb0, vshift);
      const __m128i vbh0 = _mm_and_si128(vb0, vmask);
      const __m128i vxb0 = _mm_perm_epi8(vbl0, vbh0, vpermlo);

      vacc0x0 = _mm_maddd_epi16(vxa0, vxb0, vacc0x0);
      vacc1x0 = _mm_maddd_epi16(vxa1, vxb0, vacc1x0);
      const __m128i vb1 = _mm_cvtsi32_si128((int) unaligned_load_u32((const int8_t*) w + 4));
      const __m128i vbl1 = _mm_shl_epi8(vb1, vshift);
      const __m128i vbh1 = _mm_and_si128(vb1, vmask);
      const __m128i vxb1 = _mm_perm_epi8(vbl1, vbh1, vpermlo);

      vacc0x1 = _mm_maddd_epi16(vxa0, vxb1, vacc0x1);
      vacc1x1 = _mm_maddd_epi16(vxa1, vxb1, vacc1x1);
      const __m128i vb2 = _mm_cvtsi32_si128((int) unaligned_load_u32((const int8_t*) w + 8));
      const __m128i vbl2 = _mm_shl_epi8(vb2, vshift);
      const __m128i vbh2 = _mm_and_si128(vb2, vmask);
      const __m128i vxb2 = _mm_perm_epi8(vbl2, vbh2, vpermlo);

      vacc0x2 = _mm_maddd_epi16(vxa0, vxb2, vacc0x2);
      vacc1x2 = _mm_maddd_epi16(vxa1, vxb2, vacc1x2);
      const __m128i vb3 = _mm_cvtsi32_si128((int) unaligned_load_u32((const int8_t*) w + 12));
      const __m128i vbl3 = _mm_shl_epi8(vb3, vshift);
      const __m128i vbh3 = _mm_and_si128(vb3, vmask);
      const __m128i vxb3 = _mm_perm_epi8(vbl3, vbh3, vpermlo);

      vacc0x3 = _mm_maddd_epi16(vxa0, vxb3, vacc0x3);
      vacc1x3 = _mm_maddd_epi16(vxa1, vxb3, vacc1x3);

      w = (const int8_t*) w + 16;
      k -= 8 * sizeof(int8_t);
    }

    const __m128i vacc0x01 = _mm_hadd_epi32(vacc0x0, vacc0x1);
    const __m128i vacc0x23 = _mm_hadd_epi32(vacc0x2, vacc0x3);
    const __m128i vacc1x01 = _mm_hadd_epi32(vacc1x0, vacc1x1);
    const __m128i vacc1x23 = _mm_hadd_epi32(vacc1x2, vacc1x3);

    __m128i vacc0x0123 = _mm_hadd_epi32(vacc0x01, vacc0x23);
    __m128i vacc1x0123 = _mm_hadd_epi32(vacc1x01, vacc1x23);

    vacc0x0123 = _mm_srai_epi32(vacc0x0123, 4);
    vacc1x0123 = _mm_srai_epi32(vacc1x0123, 4);
    __m128 vout0x0123 = _mm_cvtepi32_ps(vacc0x0123);
    __m128 vout1x0123 = _mm_cvtepi32_ps(vacc1x0123);

    const __m128 vinput_scale0 = _mm_broadcast_ss(&quantization_params[0].inv_scale);
    const __m128 vinput_scale1 = _mm_broadcast_ss(&quantization_params[1].inv_scale);

    vout0x0123 = _mm_mul_ps(vout0x0123, vinput_scale0);
    vout1x0123 = _mm_mul_ps(vout1x0123, vinput_scale1);

    const __m128 vfilter_output_scale0123 = _mm_load_ps((const float*) w);
    vout0x0123 = _mm_mul_ps(vout0x0123, vfilter_output_scale0123);
    vout1x0123 = _mm_mul_ps(vout1x0123, vfilter_output_scale0123);

    const __m128 vbias0123 = _mm_load_ps((const float*) w + 4);
    w = (const float*) w + 8;
    vout0x0123 = _mm_add_ps(vout0x0123, vbias0123);
    vout1x0123 = _mm_add_ps(vout1x0123, vbias0123);

    const __m128 vmin = _mm_load_ps(params->xop.min);
    vout0x0123 = _mm_max_ps(vout0x0123, vmin);
    vout1x0123 = _mm_max_ps(vout1x0123, vmin);

    const __m128 vmax = _mm_load_ps(params->xop.max);
    vout0x0123 = _mm_min_ps(vout0x0123, vmax);
    vout1x0123 = _mm_min_ps(vout1x0123, vmax);

    if XNN_LIKELY(nc >= 4) {
      _mm_storeu_ps(c1, vout1x0123);
      _mm_storeu_ps(c0, vout0x0123);

      a0 = (const int8_t*) ((uintptr_t) a0 - kc);
      a1 = (const int8_t*) ((uintptr_t) a1 - kc);

      c0 = (float*) ((uintptr_t) c0 + cn_stride);
      c1 = (float*) ((uintptr_t) c1 + cn_stride);

      nc -= 4;
    } else {
      if (nc & 2) {
        _mm_storel_pi((__m64*) c1, vout1x0123);
        vout1x0123 = _mm_unpackhi_ps(vout1x0123, vout1x0123);
        c1 += 2;
        _mm_storel_pi((__m64*) c0, vout0x0123);
        vout0x0123 = _mm_unpackhi_ps(vout0x0123, vout0x0123);
        c0 += 2;
      }
      if (nc & 1) {
        _mm_store_ss(c1, vout1x0123);
        _mm_store_ss(c0, vout0x0123);
      }
      nc = 0;
    }
  } while (nc != 0);
}
