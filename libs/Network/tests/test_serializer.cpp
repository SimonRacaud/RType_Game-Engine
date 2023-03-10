/*
** EPITECH PROJECT, 2019
** unit tests with criterion
** File description:
** just triing
*/

#include <iostream>
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "Network/Serializable.hpp"
#include "Network/Tram/ComponentSync.hpp"
#include "Network/Tram/CreateEntityReply.hpp"
#include "Network/Tram/CreateEntityRequest.hpp"
#include "Network/Tram/DestroyEntity.hpp"
#include "Network/Tram/GetRoomList.hpp"
#include "Network/Tram/JoinCreateRoomReply.hpp"
#include "Network/Tram/JoinRoom.hpp"

using namespace Tram;

class TestComponent {
  public:
    TestComponent() = default;

    std::string label{"hello world"};
    size_t number{424};
};

static const char my_timeout = 2;

Test(component_sync, deserialize, .timeout = my_timeout)
{
    TestComponent *ptr = new TestComponent;
    auto type = std::type_index(typeid(TestComponent));
    const size_t compSize = sizeof(TestComponent);
    Time time = (Time) 424242;
    ComponentSync sync(42, time, type, compSize, (void *) ptr);
    uint8_t *buffer = sync.serialize();

    sync.deserialize(buffer);
    cr_assert_eq(sync.networkId, 42);
    cr_assert_eq(sync.timestamp, time);
    cr_assert_eq(sync.componentType, type.hash_code());
    cr_assert_eq(sync.componentSize, compSize);
    TestComponent *ptr2 = reinterpret_cast<TestComponent *>(sync.component);
    cr_assert_eq(ptr2->label, "hello world");
    delete[] buffer;
}

Test(create_entity_reply, deserialize, .timeout = my_timeout)
{
    CreateEntityReply a(true, 42, 44);
    CreateEntityReply b(false, 0, 0);

    uint8_t *buffer = a.serialize();
    b.deserialize(buffer);
    cr_assert_eq(b.accept, a.accept);
    cr_assert_eq(b.entityId, a.entityId);
    cr_assert_eq(b.networkId, a.networkId);
}

Test(GetRoomList, deserialize, .timeout = my_timeout)
{
    const std::vector<size_t> list = {0, 1, 2, 3, 4, 5};
    GetRoomList a(list);
    GetRoomList b;

    uint8_t *buffer = a.serialize();
    b.deserialize(buffer);
    cr_assert_eq(b.nbItem, a.nbItem);
    for (size_t i = 0; i < list.size(); i++) {
        cr_assert_eq(b.list[i], a.list[i]);
    }
    delete[] buffer;
}