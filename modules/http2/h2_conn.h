/* Copyright 2015 greenbytes GmbH (https://www.greenbytes.de)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __mod_h2__h2_conn__
#define __mod_h2__h2_conn__

struct h2_task;
struct h2_task_env;
struct h2_worker;

/* Process the connection that is now starting the HTTP/2
 * conversation. Return when the HTTP/2 session is done
 * and the connection will close.
 */
apr_status_t h2_conn_main(conn_rec *c);

/* Process the request that has been upgraded to a HTTP/2
 * conversation. Return when the HTTP/2 session is done
 * and the connection will close.
 */
apr_status_t h2_conn_rprocess(request_rec *r);

/* Initialize this child process for h2 connection work,
 * to be called once during child init before multi processing
 * starts.
 */
apr_status_t h2_conn_child_init(apr_pool_t *pool, server_rec *s);


typedef enum {
    H2_MPM_UNKNOWN,
    H2_MPM_WORKER,
    H2_MPM_EVENT,
    H2_MPM_PREFORK,
} h2_mpm_type_t;

h2_mpm_type_t h2_conn_mpm_type();
module *h2_conn_mpm_module();

/* Returns the type of MPM module detected */
h2_mpm_type_t h2_conn_mpm_type(void);

/* Gives the detected module itself or NULL if unknown */
module *h2_conn_mpm_module(void);


conn_rec *h2_conn_create(conn_rec *master, apr_pool_t *stream_pool);

apr_status_t h2_conn_init(struct h2_task_env *env, struct h2_worker *worker);

apr_status_t h2_conn_setup(struct h2_task_env *env, struct h2_worker *worker);
apr_status_t h2_conn_prep(struct h2_task_env *env, conn_rec *master, 
                          struct h2_worker *worker);
apr_status_t h2_conn_post(conn_rec *c, struct h2_worker *worker);

apr_status_t h2_conn_process(conn_rec *c, apr_socket_t *socket);

#endif /* defined(__mod_h2__h2_conn__) */
