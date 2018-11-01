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

#ifndef _WCDB_SYNTAXCREATETRIGGERSTMT_HPP
#define _WCDB_SYNTAXCREATETRIGGERSTMT_HPP

#include <WCDB/SyntaxIdentifier.hpp>

namespace WCDB {

namespace Syntax {

class InsertSTMT;
class DeleteSTMT;
class UpdateSTMT;
class SelectSTMT;

class CreateTriggerSTMT : public Identifier {
#pragma mark - Lang
public:
    bool temp = false;
    bool ifNotExists = false;
    Schema schema;
    String trigger;
    enum class Timing {
        Before,
        After,
        InsteadOf,
    } timing;
    bool specifiedTiming = false;
    enum class Event {
        Delete,
        Insert,
        Update,
    } event;
    std::list<Column> columns;
    String table;
    bool forEachFow = false;
    Expression condition;
    bool useCondition = false;

    enum class STMT {
        Insert,
        Update,
        Delete,
        Select,
    };
    std::list<STMT> stmts;
    std::list<InsertSTMT> inserts;
    std::list<SelectSTMT> selects;
    std::list<UpdateSTMT> updates;
    std::list<DeleteSTMT> deletes;

#pragma mark - Identifier
public:
    static constexpr const Type type = Type::CreateTriggerSTMT;
    Type getType() const override final;
    String getDescription() const override final;
    void iterate(const Iterator& iterator, void* parameter) override final;
};

} // namespace Syntax

} // namespace WCDB

#endif /* _WCDB_SYNTAXCREATETRIGGERSTMT_HPP */
