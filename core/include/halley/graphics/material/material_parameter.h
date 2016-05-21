#pragma once

namespace Halley
{
	class Texture;
	class VideoAPIInternal;
	enum class ShaderParameterType;

	class MaterialParameter
	{
		friend class Material;

	public:
		void operator=(std::shared_ptr<Texture> texture);
		void operator=(Colour colour);
		void operator=(float p);
		void operator=(Vector2f p);
		void operator=(int p);
		void operator=(Vector2i p);
		void operator=(Matrix4f m);

	private:
		MaterialParameter(Material& material, String name, ShaderParameterType type);
		VideoAPIInternal& getAPI();

		void updateAddresses();
		unsigned int getAddress(int pass);
		void bind(int pass);

		std::function<void(int)> toBind;
		std::function<void(int, void*)> bindFunc;

		std::vector<int> addresses;
		Material& material;
		String name;
		ShaderParameterType type;
		bool needsTextureUnit = false;
		int textureUnit = -1;
	};

}