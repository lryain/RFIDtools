/**
 * \file pkcs5.h
 *
 * \brief PKCS#5 functions
 *
 * \author Mathias Olsson <mathias@kompetensum.com>
 */
/*
 *  Copyright (C) 2006-2015, ARM Limited, All Rights Reserved
 *  SPDX-License-Identifier: GPL-2.0
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *  This file is part of mbed TLS (https://tls.mbed.org)
 */
#ifndef MBEDTLS_PKCS5_H
#define MBEDTLS_PKCS5_H

#include "asn1.h"
#include "md.h"

#include <stddef.h>
#include <stdint.h>

#define MBEDTLS_ERR_PKCS5_BAD_INPUT_DATA                  -0x2f80  /**< Bad input parameters to function. */
#define MBEDTLS_ERR_PKCS5_INVALID_FORMAT                  -0x2f00  /**< Unexpected ASN.1 data. */
#define MBEDTLS_ERR_PKCS5_FEATURE_UNAVAILABLE             -0x2e80  /**< Requested encryption or digest alg not available. */
#define MBEDTLS_ERR_PKCS5_PASSWORD_MISMATCH               -0x2e00  /**< Given private key password does not allow for correct decryption. */

#define MBEDTLS_PKCS5_DECRYPT      0
#define MBEDTLS_PKCS5_ENCRYPT      1

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief          PKCS#5 PBES2 function
 *
 * \param pbe_params the ASN.1 algorithm parameters
 * \param mode       either MBEDTLS_PKCS5_DECRYPT or MBEDTLS_PKCS5_ENCRYPT
 * \param pwd        password to use when generating key
 * \param pwdlen     length of password
 * \param data       data to process
 * \param datalen    length of data
 * \param output     output buffer
 *
 * \returns        0 on success, or a MBEDTLS_ERR_XXX code if verification fails.
 */
int mbedtls_pkcs5_pbes2(const mbedtls_asn1_buf *pbe_params, int mode,
                        const unsigned char *pwd,  size_t pwdlen,
                        const unsigned char *data, size_t datalen,
                        unsigned char *output);

/**
 * \brief          PKCS#5 PBKDF2 using HMAC
 *
 * \param ctx      Generic HMAC context
 * \param password Password to use when generating key
 * \param plen     Length of password
 * \param salt     Salt to use when generating key
 * \param slen     Length of salt
 * \param iteration_count       Iteration count
 * \param key_length            Length of generated key in bytes
 * \param output   Generated key. Must be at least as big as key_length
 *
 * \returns        0 on success, or a MBEDTLS_ERR_XXX code if verification fails.
 */
int mbedtls_pkcs5_pbkdf2_hmac(mbedtls_md_context_t *ctx, const unsigned char *password,
                              size_t plen, const unsigned char *salt, size_t slen,
                              unsigned int iteration_count,
                              uint32_t key_length, unsigned char *output);

/**
 * \brief          Checkup routine
 *
 * \return         0 if successful, or 1 if the test failed
 */
int mbedtls_pkcs5_self_test(int verbose);

#ifdef __cplusplus
}
#endif

#endif /* pkcs5.h */