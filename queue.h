#pragma once

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

struct queue_item
{
    struct queue_item *next;
    struct queue_item *prev;
};

#define QUEUE_ITEM_INITIALIZER { .next = NULL, .prev = NULL }

static inline void queue_init(struct queue_item *q)
{
    q->next = q;
    q->prev = q;
}

static inline void queue_insert_before(struct queue_item *q, struct queue_item *t)
{
    if (t->next != NULL) {
        return;
    }
    t->next = q;
    t->prev = q->prev;
    q->prev->next = t;
    q->prev = t;
}

static inline void queue_insert_after(struct queue_item *q, struct queue_item *t)
{
    if (t->next != NULL) {
        return;
    }
    t->next = q->next;
    t->prev = q;
    q->next->prev = t;
    q->next = t;
}

static inline void queue_replace(struct queue_item *q, struct queue_item *t)
{
    if (t->next != NULL) {
        return;
    }
    t->next = q->next;
    t->prev = q->prev;
    q->next->prev = t;
    q->prev->next = t;
    q->next = NULL;
}

static inline void queue_remove_nocheck(struct queue_item *t)
{
    t->next->prev = t->prev;
    t->prev->next = t->next;
    t->next = NULL;
}

static inline void queue_remove(struct queue_item *t)
{
    if (t->next == NULL) {
        return;
    }
    queue_remove_nocheck(t);
}

static inline struct queue_item *queue_dequeue(struct queue_item *q)
{
    struct queue_item *r = q->next;
    if (r == q) {
        return NULL;
    }
    queue_remove_nocheck(r);
    return r;
}

#ifdef __cplusplus
}
#endif
