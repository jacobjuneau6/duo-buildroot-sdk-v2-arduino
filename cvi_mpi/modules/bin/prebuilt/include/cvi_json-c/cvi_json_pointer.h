/*
 * Copyright (c) 2016 Alexadru Ardelean.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the MIT license. See COPYING for details.
 *
 */

/**
 * @file
 * @brief JSON Pointer (RFC 6901) implementation for retrieving
 *        objects from a cvi_json-c object tree.
 */
#ifndef _cvi_json_pointer_h_
#define _cvi_json_pointer_h_

#include "cvi_json_object.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Retrieves a JSON sub-object from inside another JSON object
 * using the JSON pointer notation as defined in RFC 6901
 *   https://tools.ietf.org/html/rfc6901
 *
 * The returned JSON sub-object is equivalent to parsing manually the
 * 'obj' JSON tree ; i.e. it's not a new object that is created, but rather
 * a pointer inside the JSON tree.
 *
 * Internally, this is equivalent to doing a series of 'cvi_json_object_object_get()'
 * and 'cvi_json_object_array_get_idx()' along the given 'path'.
 *
 * Note that the 'path' string supports 'printf()' type arguments, so, whatever
 * is added after the 'res' param will be treated as an argument for 'path'
 * Example: cvi_json_pointer_get(obj, "/foo/%d/%s", &res, 0, bar)
 * This means, that you need to escape '%' with '%%' (just like in printf())
 *
 * @param obj the cvi_json_object instance/tree from where to retrieve sub-objects
 * @param path a (RFC6901) string notation for the sub-object to retrieve
 * @param res a pointer that stores a reference to the cvi_json_object
 *              associated with the given path
 *
 * @return negative if an error (or not found), or 0 if succeeded
 */
// #ifndef REMOVE_UNUSED_FUNCTION
JSON_EXPORT int cvi_json_pointer_get(struct cvi_json_object *obj, const char *path,
                                 struct cvi_json_object **res);

/**
 * This is a variant of 'cvi_json_pointer_get()' that supports printf() style arguments.
 *
 * Example: cvi_json_pointer_getf(obj, res, "/foo/%d/%s", 0, bak)
 * This also means that you need to escape '%' with '%%' (just like in printf())
 *
 * Please take into consideration all recommended 'printf()' format security
 * aspects when using this function.
 *
 * @param obj the cvi_json_object instance/tree to which to add a sub-object
 * @param res a pointer that stores a reference to the cvi_json_object
 *              associated with the given path
 * @param path_fmt a printf() style format for the path
 *
 * @return negative if an error (or not found), or 0 if succeeded
 */
JSON_EXPORT int cvi_json_pointer_getf(struct cvi_json_object *obj, struct cvi_json_object **res,
                                  const char *path_fmt, ...);

/**
 * Sets JSON object 'value' in the 'obj' tree at the location specified
 * by the 'path'. 'path' is JSON pointer notation as defined in RFC 6901
 *   https://tools.ietf.org/html/rfc6901
 *
 * Note that 'obj' is a double pointer, mostly for the "" (empty string)
 * case, where the entire JSON object would be replaced by 'value'.
 * In the case of the "" path, the object at '*obj' will have it's refcount
 * decremented with 'cvi_json_object_put()' and the 'value' object will be assigned to it.
 *
 * For other cases (JSON sub-objects) ownership of 'value' will be transferred into
 * '*obj' via 'cvi_json_object_object_add()' & 'cvi_json_object_array_put_idx()', so the
 * only time the refcount should be decremented for 'value' is when the return value of
 * 'cvi_json_pointer_set()' is negative (meaning the 'value' object did not get set into '*obj').
 *
 * That also implies that 'cvi_json_pointer_set()' does not do any refcount incrementing.
 * (Just that single decrement that was mentioned above).
 *
 * Note that the 'path' string supports 'printf()' type arguments, so, whatever
 * is added after the 'value' param will be treated as an argument for 'path'
 * Example: cvi_json_pointer_set(obj, "/foo/%d/%s", value, 0, bak)
 * This means, that you need to escape '%' with '%%' (just like in printf())
 *
 * @param obj the cvi_json_object instance/tree to which to add a sub-object
 * @param path a (RFC6901) string notation for the sub-object to set in the tree
 * @param value object to set at path
 *
 * @return negative if an error (or not found), or 0 if succeeded
 */
JSON_EXPORT int cvi_json_pointer_set(struct cvi_json_object **obj, const char *path,
                                 struct cvi_json_object *value);

/**
 * This is a variant of 'cvi_json_pointer_set()' that supports printf() style arguments.
 *
 * Example: cvi_json_pointer_setf(obj, value, "/foo/%d/%s", 0, bak)
 * This also means that you need to escape '%' with '%%' (just like in printf())
 *
 * Please take into consideration all recommended 'printf()' format security
 * aspects when using this function.
 *
 * @param obj the cvi_json_object instance/tree to which to add a sub-object
 * @param value object to set at path
 * @param path_fmt a printf() style format for the path
 *
 * @return negative if an error (or not found), or 0 if succeeded
 */
JSON_EXPORT int cvi_json_pointer_setf(struct cvi_json_object **obj, struct cvi_json_object *value,
                                  const char *path_fmt, ...);
#endif
#ifdef __cplusplus
}
#endif

// #endif
