#include <mbgl/layermanager/symbol_layer_factory.hpp>

#include <mbgl/layout/symbol_layout.hpp>
#include <mbgl/renderer/layers/render_symbol_layer.hpp>
#include <mbgl/style/layers/symbol_layer.hpp>
#include <mbgl/style/layers/symbol_layer_impl.hpp>

namespace mbgl {

const style::LayerTypeInfo* SymbolLayerFactory::getTypeInfo() const noexcept {
    return style::SymbolLayer::Impl::staticTypeInfo();
}

std::unique_ptr<style::Layer> SymbolLayerFactory::createLayer(const std::string& id,
                                                              const style::conversion::Convertible& value) noexcept {
    const auto source = getSource(value);
    return std::unique_ptr<style::Layer>(source ? new (std::nothrow) style::SymbolLayer(id, *source) : nullptr);
}

std::unique_ptr<Layout> SymbolLayerFactory::createLayout(const LayoutParameters& parameters,
                                                         std::unique_ptr<GeometryTileLayer> tileLayer,
                                                         const std::vector<Immutable<style::LayerProperties>>& group) {
    return std::unique_ptr<Layout>(
        new (std::nothrow) SymbolLayout(parameters.bucketParameters, group, std::move(tileLayer), parameters));
}

std::unique_ptr<RenderLayer> SymbolLayerFactory::createRenderLayer(Immutable<style::Layer::Impl> impl) noexcept {
    assert(impl->getTypeInfo() == getTypeInfo());
    return std::make_unique<RenderSymbolLayer>(staticImmutableCast<style::SymbolLayer::Impl>(impl));
}

} // namespace mbgl
