/*
 *  LibNoPoll: A websocket library
 *  Copyright (C) 2024 Advanced Software Production Line, S.L.
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public License
 *  as published by the Free Software Foundation; either version 2.1
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this program; if not, write to the Free
 *  Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 *  02111-1307 USA
 *
 *  You may find a copy of the license under this software is released
 *  at COPYING file. This is LGPL software: you are welcome to develop
 *  proprietary applications using this library without any royalty or
 *  fee but returning back any change, improvement or addition in the
 *  form of source code, project image, documentation patches, etc.
 *
 *  For commercial support on build Websocket enabled solutions
 *  contact us:
 *
 *      Postal address:
 *         Advanced Software Production Line, S.L.
 *         Av. Juan Carlos I, Nº13, 2ºC
 *         Alcalá de Henares 28806 Madrid
 *         Spain
 *
 *      Email address:
 *         info@aspl.es - http://www.aspl.es/nopoll
 */
#include <nopoll_decl.h>

/**
 * \addtogroup nopoll_decl_module
 * @{
 */

#if !(NOPOLL_OS_RTTHREAD)
/**
 * @brief Calloc helper for nopoll library.
 *
 * @param count How many items to allocate.
 * @param size Size of one item.
 *
 * @return A newly allocated pointer.
 * @see nopoll_free
 */
noPollPtr nopoll_calloc(size_t count, size_t size)
{
    return calloc (count, size);
}

/**
 * @brief Realloc helper for nopoll library.
 *
 * @param ref the reference to reallocate.
 * @param size Size of the new reference.
 *
 * @return A newly allocated pointer.
 * @see nopoll_free
 */
noPollPtr nopoll_realloc(noPollPtr ref, size_t size)
{
    return realloc (ref, size);
}

/**
 * @brief Allows to deallocate memory referenced by <i>ref</i> but
 * checking before that the reference is different from null.
 *
 * @param ref The reference to clear.
 */
void nopoll_free (noPollPtr ref)
{
    free (ref);
    return;
}
#endif

/**
 * @}
 */

