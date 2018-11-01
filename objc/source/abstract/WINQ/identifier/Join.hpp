/*
 * Tencent is pleased to support the open source community by making
 * WCDB available.
 *
 * Copyright (C) 2017 THL A29 Limited, a Tencent company.
 * All rights reserved.
 *
 * Licensed under the BSD 3-Clause License (the "License"); you may not use
 * this file except in compliance with the License. You may obtain a copy of
 * the License at
 *
 *       https://opensource.org/licenses/BSD-3-Clause
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _WCDB_JOIN_HPP
#define _WCDB_JOIN_HPP

#include <WCDB/SQL.hpp>

namespace WCDB {

class Join : public TypedSyntax<Syntax::JoinClause, SQL> {
public:
    using TypedSyntax<Syntax::JoinClause, SQL>::TypedSyntax;

    Join& table(const TableOrSubquery& tableOrSubquery);

    Join& with(const TableOrSubquery& tableOrSubquery);
    Join& join(const TableOrSubquery& tableOrSubquery);
    Join& leftOuterJoin(const TableOrSubquery& tableOrSubquery);
    Join& leftJoin(const TableOrSubquery& tableOrSubquery);
    Join& innerJoin(const TableOrSubquery& tableOrSubquery);
    Join& crossJoin(const TableOrSubquery& tableOrSubquery);
    Join& naturalJoin(const TableOrSubquery& tableOrSubquery);
    Join& naturalLeftOuterJoin(const TableOrSubquery& tableOrSubquery);
    Join& naturalLeftJoin(const TableOrSubquery& tableOrSubquery);
    Join& naturalInnerJoin(const TableOrSubquery& tableOrSubquery);
    Join& naturalCrossJoin(const TableOrSubquery& tableOrSubquery);

    Join& constraint(const JoinConstraint& constraint);

private:
    Join& join(const Syntax::JoinOperator& joinOperator, const TableOrSubquery& tableOrSubquery);
};

} // namespace WCDB

#endif /* _WCDB_JOIN_HPP */
