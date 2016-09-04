/*
 * deque.c
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include <stdlib.h>
#include "deque.h"

/* -- Types -- */

struct node
{
  struct node* next;
  struct node* prev;
  deque_el value;
};

struct deque
{
  struct node* front;
  struct node* back;
  size_t count;
};

/* -- Procedures -- */

deque_t deque_new()
{
  deque_t deque = (deque_t)malloc(sizeof(struct deque));
  if (!deque)
    return NULL;

  deque->front = NULL;
  deque->back = NULL;
  deque->count = 0;

  return deque;
}

void deque_delete(deque_t deque)
{
  struct node* node = deque->front;
  while (node)
  {
    struct node* tmp = node->next;
    free(node);
    node = tmp;
  }

  free(deque);
}

size_t deque_count(deque_t deque)
{
  return deque->count;
}

taocp_err deque_push_front(deque_t deque, deque_el el)
{
  struct node* node = (struct node*)malloc(sizeof(struct node));
  if (!node)
    return TAOCP_ERR_MEMORY;

  node->value = el;
  node->prev = NULL;
  node->next = deque->front;

  if (deque->count == 0)
  {
    deque->front = node;
    deque->back = node;
  }
  else
  {
    deque->front->prev = node;
    deque->front = node;
  }

  deque->count++;
  return TAOCP_ERR_OK;
}

taocp_err deque_pop_front(deque_t deque, deque_el* out_el)
{
  if (deque->count == 0)
    return TAOCP_ERR_UNDERFLOW;

  struct node* node = deque->front;
  *out_el = node->value;

  if (deque->count == 1)
  {
    deque->front = NULL;
    deque->back = NULL;
  }
  else
  {
    deque->front = node->next;
    deque->front->prev = NULL;
  }

  free(node);
  deque->count--;
  return TAOCP_ERR_OK;
}

taocp_err deque_push_back(deque_t deque, deque_el el)
{
  struct node* node = (struct node*)malloc(sizeof(struct node));
  if (!node)
    return TAOCP_ERR_MEMORY;

  node->value = el;
  node->prev = deque->back;
  node->next = NULL;

  if (deque->count == 0)
  {
    deque->front = node;
    deque->back = node;
  }
  else
  {
    deque->back->next = node;
    deque->back = node;
  }

  deque->count++;
  return TAOCP_ERR_OK;
}

taocp_err deque_pop_back(deque_t deque, deque_el* out_el)
{
  if (deque->count == 0)
    return TAOCP_ERR_UNDERFLOW;

  struct node* node = deque->back;
  *out_el = node->value;

  if (deque->count == 1)
  {
    deque->front = NULL;
    deque->back = NULL;
  }
  else
  {
    deque->back = node->prev;
    deque->back->next = NULL;
  }

  free(node);
  deque->count--;
  return TAOCP_ERR_OK;
}
