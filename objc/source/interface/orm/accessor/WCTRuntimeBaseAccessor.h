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

#import <WCDB/WCTCommon.h>
#import <functional>

class WCTRuntimeBaseAccessor {
public:
    virtual ~WCTRuntimeBaseAccessor() = 0;

protected:
    using InstanceType = id;
    static SEL getGetterSelector(Class cls, const WCDB::String &propertyName);
    static SEL getSetterSelector(Class cls, const WCDB::String &propertyName);
    static IMP getClassMethodImplementation(Class cls, SEL selector);
    static IMP getInstanceMethodImplementation(Class cls, SEL selector);
    static Class getPropertyClass(Class cls, const WCDB::String &propertyName);
};

template<typename PropertyType>
class WCTRuntimeAccessor : public WCTRuntimeBaseAccessor {
public:
    using Setter = void (^)(InstanceType, PropertyType);
    using Getter = PropertyType (^)(InstanceType);

    WCTRuntimeAccessor(Class cls, const WCDB::String &propertyName)
    : getProperty(GenerateGetter(cls, propertyName))
    , setProperty(GenerateSetter(cls, propertyName))
    {
    }

    virtual ~WCTRuntimeAccessor() {}

    const Setter setProperty;
    const Getter getProperty;

protected:
    Getter GenerateGetter(Class cls, const WCDB::String &propertyName)
    {
        SEL selector = getGetterSelector(cls, propertyName);
        IMP imp = getInstanceMethodImplementation(cls, selector);
        auto block = ^(InstanceType instance) {
            using IMPGetter = PropertyType (*)(id, SEL);
            return ((IMPGetter) imp)(instance, selector);
        };
        return [block copy];
    }

    Setter GenerateSetter(Class cls, const WCDB::String &propertyName)
    {
        SEL selector = getSetterSelector(cls, propertyName);
        IMP imp = getInstanceMethodImplementation(cls, selector);
        auto block = ^(InstanceType instance, PropertyType value) {
            using IMPSetter = void (*)(InstanceType, SEL, PropertyType);
            return ((IMPSetter) imp)(instance, selector, value);
        };
        return [block copy];
    }
};
