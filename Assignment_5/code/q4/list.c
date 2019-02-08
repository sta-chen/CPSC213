#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "list.h"

struct list {
  struct element* head;
  struct element* tail;
};

struct element {
  char*           value;
  struct element* prev;
  struct element* next;
};

/**
 * Create new list
 */
struct list* list_new() {
  struct list* l = malloc (sizeof (*l));
  l->head = l->tail = NULL;
  return l;
}

/**
 * Delete the list (including its elements).
 */
void list_delete (struct list* l) {
  for (struct element *e = l->head, *n; e != NULL; e = n) {
    n = e->next;
    list_delete_element (l, e);
  }
  free (l);
}

/**
 * Add an element to the list.
 * Returns pointer to newly added element.
 */
struct element* list_add_element (struct list* l, char* value) {
  struct element* e   = malloc (sizeof (*e));
  int value_len = strlen (value);
  e->value      = malloc (value_len + 1);
  strncpy (e->value, value, value_len);
  e->prev = e->next = NULL;
  if (l->head == NULL)
    l->head = e;
  else {
    l->tail->next = e;
    e->prev       = l->tail;
  }
  l->tail = e;
  return e;
}

/**
 * Remove element from list and free it
 */
void list_delete_element (struct list* l, struct element* e) {
  if (e == l->head)
    l->head = e->next;
  else
    e->prev->next = e->next;
  if (e == l->tail)
    l->tail = e->prev;
  else
    e->next->prev = e->prev;
  e->next = e->prev = NULL;
  free (e->value);
  free (e);
}

/**
 * Get first element of list.
 */
struct element* list_get_first_element (struct list* l) {
  return l->head;
}

/**
 * Get next element of list.
 */
struct element* element_get_next (struct element* e) {
  return e->next;
}

/**
 * Get element's value
 */
char* element_get_value (struct element* e) {
  return e->value;
}

/**
 * Increment element's reference count.
 */
void element_keep_ref (struct element* e) {
  // TODO
}

/**
 * Decrement element's reference count and free element when count goes to 0.
 */
void element_free_ref (struct element* e) {
  // TODO
}
