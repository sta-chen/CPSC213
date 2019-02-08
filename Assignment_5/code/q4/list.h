#ifndef __list_h__
#define __list_h__

struct list;
struct element;

/**
 * Create new list
 */
struct list* list_new();

/**
 * Delete the list and all of the elements it contains.
 */
void list_delete (struct list* l);

/**
 * Add an element to the list.
 * Returns pointer to new element.
 */
struct element* list_add_element (struct list* l, char* value);

/**
 * Remove element from list and decrement its reference count.
 */
void list_delete_element (struct list* l, struct element* e);

/**
 * Get first element of list. 
 */
struct element* list_get_first_element (struct list* l);

/**
 * Get next element of list.
 */
struct element* element_get_next (struct element* e);

/**
 * Get element's value
 */
char* element_get_value (struct element* e);

/**
 * Increment element's reference count.
 */
void element_keep_ref (struct element* e);

/**
 * Decrement element's reference count and free element when count goes to 0.
 */
void element_free_ref (struct element* e);

#endif /* __list_h__ */
