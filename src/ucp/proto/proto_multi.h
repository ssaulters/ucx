/**
 * Copyright (C) Mellanox Technologies Ltd. 2020.  ALL RIGHTS RESERVED.
 *
 * See file LICENSE for terms.
 */

#ifndef UCP_PROTO_MULTI_H_
#define UCP_PROTO_MULTI_H_

#include "proto.h"
#include "proto_common.h"


/**
 * UCP base protocol definition for multi-fragment protocols
 */
typedef struct ucp_proto_send_multi {
    ucp_proto_t                    super;
    ptrdiff_t                      iface_fragsz_offset; /* Offset of fragment
                                                           size in iface attr */
} ucp_proto_send_multi_t;


/*
 * One lane configuration for multi-lane protocol
 */
typedef struct {
    ucp_lane_index_t               lane;       /* Lane to use */
    size_t                         max_frag;   /* Max frag size on this lane */
    double                         weight;     /* Relative weight for this lane */
} ucp_proto_multi_lane_priv_t;


/*
 * Base class for protocols with fragmentation
 */
typedef struct {
    ucp_lane_index_t               num_lanes;  /* Number of lanes to use */
    ucp_md_map_t                   reg_md_map; /* Memory domains to register on */
    ucp_proto_multi_lane_priv_t    lanes[0];   /* Array of lanes */
} ucp_proto_multi_priv_t;


/**
 * Initialization parameters for multi-lane protocol
 */
typedef struct {
    ucp_proto_common_init_params_t super;
    ucp_lane_index_t               max_lanes;  /* Max lanes to select */

    struct {
        uint64_t                   tl_cap_flags; /* Required iface capabilities */
        ucp_lane_type_t            lane_type;    /* Required lane type */
    } first, middle;
} ucp_proto_multi_init_params_t;


ucs_status_t ucp_proto_multi_init(const ucp_proto_multi_init_params_t *params);


void ucp_proto_multi_config_str(const void *priv, ucs_string_buffer_t *strb);

#endif
