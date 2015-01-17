/*
 * Public domain
 * sha2.h compatibility shim
 */

#ifdef HAVE_SHA2_H
#include_next <sha2.h>
#else

#if defined(__cplusplus)
#define	__BEGIN_DECLS	extern "C" {
#define	__END_DECLS	};
#else
#define	__BEGIN_DECLS
#define	__END_DECLS
#endif

#include "sha2_openbsd.h"

#define __weak_alias(alias,sym)

#define SHA224Transform(a, b) SHA256Transform(a, b)
#define SHA224Update(a, b, c) SHA256Update(a, b, c)
#define SHA224Pad(a) SHA256Pad(a)

#define SHA384Transform(a, b) SHA512Transform(a, b)
#define SHA384Update(a, b, c) SHA512Update(a, b, c)
#define SHA384Pad(a) SHA512Pad(a)

#define SHA512_CTX SHA2_CTX
#define SHA512_Init(ctx) SHA512Init(ctx)
#define SHA512_Update(ctx, buf, len) SHA512Update(ctx, (void *)buf, len)
#define SHA512_Final(digest, ctx) SHA512Final(digest, ctx)

#include <machine/endian.h>

#endif
