/* vim: ft=c ff=unix fenc=utf-8
 * file: evqueu.h
 */
#ifndef _EVQUEU_1467875624_H_
#define _EVQUEU_1467875624_H_

#include <stdbool.h>
#include <stdint.h>
#include <pthread.h>
#include <unistd.h>
#include <ev.h>

#if !defined(EV_MULTIPLICITY) || !EV_MULTIPLICITY
# error "work only with EV_MULTIPLICITY"
#endif

#define EVQ_QUEUE_BLOCK  32

struct evq_node {
	struct ev_async event;

    void (*event_cb)();

    struct evq_p2p *v;
	struct ev_loop *loop;

    size_t queue_capacity;
    size_t queue_size;
	intptr_t *queue;
};

struct evq_p2p {
    /* thread-safe pass message (pointers)
     * from one thread to another
     * with different ev's loop
     */
	struct evq_node left;
	struct evq_node right;
};

typedef void(*evq_cb_t)(struct evq_p2p *v, int id, intptr_t p);


void evq_init(struct evq_p2p *v);
void evq_free(struct evq_p2p *v);

/* attach to queue */
struct evq_node *evq_attach(struct evq_p2p *v, struct ev_loop *loop, evq_cb_t cb);
/* detach from queue */
void evq_detach(struct evq_node *p);

/* *** passing */
/* send message to queue */
bool evq_send(struct evq_node *p, void *message);
/* broadcast message to queue */
bool evq_noise(struct evq_p2p *v, void *message);

/* *** control */
/* pause incoming events */
bool evq_pause(struct evq_node *p);
/* resume incoming event */
bool evq_resume(struct evq_node *p);
/* purge incoming queue */
bool evq_purge(struct evq_node *p);

#endif /* _EVQUEU_1467875624_H_ */

