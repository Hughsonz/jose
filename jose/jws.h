/* vim: set tabstop=8 shiftwidth=4 softtabstop=4 expandtab smarttab colorcolumn=80: */
/*
 * Copyright 2016 Red Hat, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <jansson.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct jose_jws_signer {
    struct jose_jws_signer *next;

    const char **algs;
    const char *(*suggest)(const json_t *jwk);
    bool (*sign)(json_t *sig, const json_t *jwk,
                 const char *alg, const char *prot, const char *payl);
    bool (*verify)(const json_t *sig, const json_t *jwk,
                   const char *alg, const char *prot, const char *payl);
} jose_jws_signer_t;

void
jose_jws_register_signer(jose_jws_signer_t *signer);

/**
 * Converts a JWS from compact format into JSON format.
 */
json_t *
jose_jws_from_compact(const char *jws);

/**
 * Converts a JWS from JSON format into compact format.
 *
 * If more than one signature exists or if an unprotected header is found,
 * this operation will fail.
 *
 * Free with free().
 */
char *
jose_jws_to_compact(const json_t *jws);

bool
jose_jws_sign(json_t *jws, const json_t *jwk, json_t *sig);

bool
jose_jws_verify(const json_t *jws, const json_t *jwk);

json_t *
jose_jws_merge_header(const json_t *sig);
