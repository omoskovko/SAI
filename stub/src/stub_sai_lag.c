#include "sai.h"
#include "stub_sai.h"
#include "assert.h"

sai_status_t stub_remove_object(sai_object_id_t object_id)
{
    uint32_t data;
    sai_object_type_t type = sai_object_type_query(object_id);

    if (type == SAI_OBJECT_TYPE_NULL || type >= SAI_OBJECT_TYPE_MAX)
    {
        STUB_LOG_ERR("Invalid object type %d\n", type);
        return SAI_STATUS_INVALID_PARAMETER;
    }

    if (SAI_STATUS_SUCCESS != stub_object_to_type(object_id, type, &data))
    {
        STUB_LOG_ERR("Failed to convert object id to type\n");
        return SAI_STATUS_INVALID_PARAMETER;
    }

    STUB_LOG_NTC("Removed object %s with id %x\n", SAI_TYPE_STR(type), data);

    return SAI_STATUS_SUCCESS;
}

sai_status_t stub_create_lag(
    _Out_ sai_object_id_t *lag_id,
    _In_ uint32_t attr_count,
    _In_ sai_attribute_t *attr_list)
{
    // return SAI_STATUS_NOT_IMPLEMENTED;
    static int32_t next_lag_id = 1;
    sai_status_t status;
    status = stub_create_object(SAI_OBJECT_TYPE_LAG, next_lag_id++, lag_id);
    if (status != SAI_STATUS_SUCCESS)
    {
        printf("Cannot create a LAG OID\n");
        return status;
    }

    printf("CREATE LAG: 0x%lX\n", *lag_id);
    return SAI_STATUS_SUCCESS;
}

sai_status_t stub_remove_lag(
    _In_ sai_object_id_t lag_id)
{
    sai_status_t status;
    status = stub_remove_object(lag_id);
    if (status != SAI_STATUS_SUCCESS)
    {
        printf("Cannot remove LAG OID\n");
        return status;
    }

    printf("REMOVE LAG: 0x%lX\n", lag_id);
    return SAI_STATUS_SUCCESS;
}

sai_status_t stub_set_lag_attribute(
    _In_ sai_object_id_t lag_id,
    _In_ const sai_attribute_t *attr)
{
    printf("SET LAG ATTRIBUTE: {LAG_ID: 0x%lX}\n", lag_id);
    return SAI_STATUS_SUCCESS;
}

sai_status_t stub_get_lag_attribute(
    _In_ sai_object_id_t lag_id,
    _In_ uint32_t attr_count,
    _Inout_ sai_attribute_t *attr_list)
{
    printf("GET LAG ATTRIBUTE: {LAG_ID: 0x%lX}\n", lag_id);
    return SAI_STATUS_SUCCESS;
}

sai_status_t stub_create_lag_member(
    _Out_ sai_object_id_t *lag_member_id,
    _In_ uint32_t attr_count,
    _In_ sai_attribute_t *attr_list)
{
    static int32_t next_lag_member_id = 1;
    sai_status_t status;
    sai_object_id_t port_id = SAI_NULL_OBJECT_ID;
    sai_object_id_t lag_id = SAI_NULL_OBJECT_ID;
    bool port_id_found = false;
    bool lag_id_found = false;

    // Check for mandatory SAI_LAG_MEMBER_ATTR_PORT_ID and SAI_LAG_MEMBER_ATTR_LAG_ID attributes
    for (uint32_t i = 0; i < attr_count; i++)
    {
        if (attr_list[i].id == SAI_LAG_MEMBER_ATTR_PORT_ID)
        {
            port_id = attr_list[i].value.oid;
            port_id_found = true;
        }
        if (attr_list[i].id == SAI_LAG_MEMBER_ATTR_LAG_ID)
        {
            lag_id = attr_list[i].value.oid;
            lag_id_found = true;
        }
    }

    if (!port_id_found)
    {
        printf("Missing mandatory attribute SAI_LAG_MEMBER_ATTR_PORT_ID\n");
        return SAI_STATUS_MANDATORY_ATTRIBUTE_MISSING;
    }

    if (!lag_id_found)
    {
        printf("Missing mandatory attribute SAI_LAG_MEMBER_ATTR_LAG_ID\n");
        return SAI_STATUS_MANDATORY_ATTRIBUTE_MISSING;
    }

    status = stub_create_object(SAI_OBJECT_TYPE_LAG_MEMBER, next_lag_member_id++, lag_member_id);
    if (status != SAI_STATUS_SUCCESS)
    {
        printf("Cannot create a LAG member OID\n");
        return status;
    }

    printf("CREATE LAG MEMBER: 0x%lX {LAG_ID: 0x%lX, PORT_ID: 0x%lX}\n", *lag_member_id, lag_id, port_id);
    return SAI_STATUS_SUCCESS;
}

sai_status_t stub_remove_lag_member(
    _In_ sai_object_id_t lag_member_id)
{
    sai_status_t status;
    status = stub_remove_object(lag_member_id);
    if (status != SAI_STATUS_SUCCESS)
    {
        printf("Cannot remove LAG member OID\n");
        return status;
    }

    printf("REMOVE LAG MEMBER: 0x%lX\n", lag_member_id);
    return SAI_STATUS_SUCCESS;
}

sai_status_t stub_set_lag_member_attribute(
    _In_ sai_object_id_t lag_member_id,
    _In_ const sai_attribute_t *attr)
{
    printf("SET LAG MEMBER ATTRIBUTE: {LAG_MEMBER_ID: 0x%lX}\n", lag_member_id);
    return SAI_STATUS_SUCCESS;
}

sai_status_t stub_get_lag_member_attribute(
    _In_ sai_object_id_t lag_member_id,
    _In_ uint32_t attr_count,
    _Inout_ sai_attribute_t *attr_list)
{
    printf("GET LAG MEMBER ATTRIBUTE: {LAG_MEMBER_ID: 0x%lX}\n", lag_member_id);
    return SAI_STATUS_SUCCESS;
}

const sai_lag_api_t lag_api = {
    stub_create_lag,
    stub_remove_lag,
    stub_set_lag_attribute,
    stub_get_lag_attribute,
    stub_create_lag_member,
    stub_remove_lag_member,
    stub_set_lag_member_attribute,
    stub_get_lag_member_attribute};