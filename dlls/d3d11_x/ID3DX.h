#pragma once
#include "pch.h"
#include "d3d_x/d3d11_x_device.h"
#include "d3d_x/d3d_x.hpp"


namespace d3d11x
{
	
    struct D3D11X_DESCRIPTOR_TEXTURE_VIEW
    {
        union
        {
            //__m128i Oword[ 2 ]; @Patoke todo: cannot be arsed
            unsigned __int64 Qword[ 4 ];
            unsigned int Dword[ 8 ];
        };
    };



    struct ID3D11DeviceChild_X : public IGraphicsUnknown
    {
        public: ID3D11Device* m_pDevice;
        public: void* m_pPrivateData;
    public:
        virtual void STDMETHODCALLTYPE GetDevice(
            /* [annotation] */
            _Outptr_  ID3D11Device * *ppDevice) PURE;

        virtual HRESULT STDMETHODCALLTYPE GetPrivateData(
            /* [annotation] */
            _In_  REFGUID guid,
            /* [annotation] */
            _Inout_  UINT* pDataSize,
            /* [annotation] */
            _Out_writes_bytes_opt_(*pDataSize)  void* pData) PURE;

        virtual HRESULT STDMETHODCALLTYPE SetPrivateData(
            /* [annotation] */
            _In_  REFGUID guid,
            /* [annotation] */
            _In_  UINT DataSize,
            /* [annotation] */
            _In_reads_bytes_opt_(DataSize)  const void* pData) PURE;

        virtual HRESULT STDMETHODCALLTYPE SetPrivateDataInterface(
            /* [annotation] */
            _In_  REFGUID guid,
            /* [annotation] */
            _In_opt_  const IUnknown* pData) PURE;


        // Xbox Extra functions:
        virtual HRESULT STDMETHODCALLTYPE SetPrivateDataInterfaceGraphics(const _GUID& name, const IGraphicsUnknown* data)
        {
            return SetPrivateDataInterface(name, reinterpret_cast<IUnknown const*>(data));
        }

        virtual HRESULT STDMETHODCALLTYPE SetName(const wchar_t* name) PURE;
    };



    struct ID3D11Resource_X : public ID3D11DeviceChild_X
    {
    
        virtual void STDMETHODCALLTYPE GetType(
            /* [annotation] */
            _Out_  D3D11_RESOURCE_DIMENSION * pResourceDimension) PURE;

        virtual void STDMETHODCALLTYPE SetEvictionPriority(
            /* [annotation] */
            _In_  UINT EvictionPriority) PURE;

        virtual UINT STDMETHODCALLTYPE GetEvictionPriority(void) PURE;
        // xbox extra function
        virtual void STDMETHODCALLTYPE GetDescriptor(D3D11X_DESCRIPTOR_RESOURCE* descriptor) PURE;
    };

    struct ID3D11Texture1D_X : public ID3D11Resource_X
    {

        virtual void STDMETHODCALLTYPE GetDesc(
            /* [annotation] */
            _Out_  D3D11_TEXTURE1D_DESC* pDesc) PURE;

    };

    struct ID3D11Texture2D_X : public ID3D11Resource_X
    {
    
        virtual void STDMETHODCALLTYPE GetDesc(
            /* [annotation] */
            _Out_  D3D11_TEXTURE2D_DESC * pDesc) PURE;

    };

    struct ID3D11Texture3D_X : public ID3D11Resource_X
    {

        virtual void STDMETHODCALLTYPE GetDesc(
            /* [annotation] */
            _Out_  D3D11_TEXTURE3D_DESC* pDesc) PURE;

    };

    struct ID3D11View_X : ID3D11DeviceChild_X
    {
    public:
        ID3D11Resource* m_pResource;
        unsigned int m_Type;

        virtual void STDMETHODCALLTYPE GetResource(
            /* [annotation] */
            _Outptr_  ID3D11Resource** ppResource) PURE;

    };

    struct ID3D11RenderTargetView_X : ID3D11View_X
    {
    public:
        virtual void STDMETHODCALLTYPE GetDesc(
            /* [annotation] */
            _Out_  D3D11_RENDER_TARGET_VIEW_DESC* pDesc) PURE;

    };

    struct ID3D11DepthStencilView_X : ID3D11View_X
    {
    public:
        virtual void STDMETHODCALLTYPE GetDesc(
            /* [annotation] */
            _Out_  D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc) PURE;

    };

    struct ID3D11ShaderResourceView_X : ID3D11View_X
    {
    public:
        virtual void STDMETHODCALLTYPE GetDesc(
            /* [annotation] */
            _Out_  D3D11_SHADER_RESOURCE_VIEW_DESC* pDesc) PURE;

    };

    struct ID3D11UnorderedAccessView_X : ID3D11View_X
    {
    public:
        D3D11X_DESCRIPTOR_TEXTURE_VIEW m_Descriptor;
        void* m_pAllocationStart;

        virtual void STDMETHODCALLTYPE GetDesc(
            /* [annotation] */
            _Out_  D3D11_UNORDERED_ACCESS_VIEW_DESC* pDesc) PURE;

    };

    struct ID3D11Buffer_X : ID3D11Resource_X
    {
    public:
        virtual void STDMETHODCALLTYPE GetDesc(
            /* [annotation] */
            _Out_  D3D11_BUFFER_DESC* pDesc) = 0;

    };
}