/* OPENBSD ORIGINAL: lib/libc/string/explicit_bzero.c
 * $OpenBSD: explicit_bzero.c,v 1.1 2014/01/22 21:06:45 tedu Exp $
 *
 * Public domain.
 */

/*
 * @file im_explicit_bzero.c
 *
 * @author Ted Unangst
 */

#include <strings.h>

#ifndef HAVE_EXPLICIT_BZERO

#ifdef HAVE_MEMSET_S

void
im_explicit_bzero(void *p, size_t n)
{
	(void)memset_s(p, n, 0, n);
}

#else /* HAVE_MEMSET_S */

/*
 * Indirect bzero through a volatile pointer to hopefully avoid
 * dead-store optimisation eliminating the call.
 */
static void (* volatile im_bzero)(void *, size_t) = bzero;

void
im_explicit_bzero(void *p, size_t n)
{
	im_bzero(p, n);
}

#endif /* HAVE_MEMSET_S */

#endif /* HAVE_EXPLICIT_BZERO */
