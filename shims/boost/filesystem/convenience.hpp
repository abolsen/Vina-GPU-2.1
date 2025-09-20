// Compatibility shim for legacy includes: boost/filesystem/convenience.hpp
// Many older projects included this header, which was removed or reorganized
// in newer Boost versions. This shim redirects to the canonical headers.

#pragma once
#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
// convenience.hpp historically contained helpers that are now in operations.hpp
// If specific helpers are missing, they likely have direct equivalents in filesystem.
