//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/test/gtest-ns.hpp"
#include "beetree/units/pose-2d.hpp"

namespace bte {
namespace test {
namespace internal {

class PoseEqualsMatcher : public gtest::MatcherInterface<const units::Pose2D&>
{
public:
    PoseEqualsMatcher(const units::Pose2D& expected);

    bool MatchAndExplain(const units::Pose2D&        actual,
                         gtest::MatchResultListener* listener) const override;
    void DescribeTo(std::ostream* os) const override;

private:
    units::Pose2D m_expected;
};
}  // namespace internal
}  // namespace test
}  // namespace bte