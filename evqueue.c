/* vim: ft=c ff=unix fenc=utf-8
 * file: evqueue.c
 */
#include <string.h>
#include <strings.h>
#include "evqueue.h"

void
evq_init(struct evq_p2p *v)
{
    memset(v, 0u, sizeof(*v));
}

void
evq_free(struct evq_p2p *v)
{
    /* TODO: check nodes */
    memset(v, 0u, sizeof(*v));
}

static void
eqv_event_cb(struct ev_loop *loop, ev_async *w, int revents)
{
    /*struct evq_node *p = (struct evq_node*)w;*/
}

struct evq_node *
evq_attach(struct evq_p2p *v, struct ev_loop *loop, evq_cb_t cb)
{
    struct evq_node *p = NULL;
    if (!loop)
        return NULL;

    if (!v->left.loop) {
        p = &v->left;
    } else if (!v->right.loop) {
        p = &v->right;
    }

    memset(p, 0u, sizeof(*p));
    p->v = v;
    p->loop = loop;

    ev_async_init(&p->event, eqv_event_cb);
    ev_async_start(p->loop, &p->event);

    p->event_cb = cb;

    return NULL;
}

void
evq_detach(struct evq_node *p)
{
    if (!p || !p->v)
        return;
    ev_async_stop(p->loop, &p->event);
    memset(p, 0u, sizeof(*p));
}

bool
evq_send(struct evq_node *p, void *message)
{
    struct evq_node *r = NULL;
    if (p == &p->v->left) {
        r = &p->v->right;
    } else (p == &p->v->right) {
        r = &p->v->left;
    } else {
        /* TODO: toLog(non-consistent structuries) */
        return false;
    }

    /* TODO: ... */

    return true;
}

