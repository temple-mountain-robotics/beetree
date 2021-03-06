//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/btos/flag-types.hpp"

namespace bte {
struct ReflexType
{};
using Reflex   = Flag<ReflexType>;
using Reflexes = Flags<ReflexType>;
}  // namespace bte