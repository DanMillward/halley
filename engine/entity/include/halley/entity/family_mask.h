#pragma once

#include <bitset>

namespace Halley {
	namespace FamilyMask {
		using RealType = std::bitset<128>;


		class Handle
		{
		public:
			Handle();
			Handle(const Handle& h);
			Handle(Handle&& h);
			Handle(const RealType& mask);
			Handle(RealType&& mask);

			void operator=(const Handle& h);

			bool operator==(const Handle& h) const;
			bool operator!=(const Handle& h) const;
			bool operator<(const Handle& h) const;
			Handle operator&(const Handle& h) const;

			const RealType& getRealValue() const;

		private:
			int value = -1;
		};

		using HandleType = Handle;


		inline void setBit(RealType& mask, int bit) {
			mask[bit] = true;
		}

		inline bool hasBit(HandleType handle, int bit) {
			return handle.getRealValue()[bit];
		}



		HandleType getHandle(RealType mask);



		template <typename... Ts>
		struct Evaluator;

		template <>
		struct Evaluator <> {
			static RealType makeMask(RealType startValue) {
				return startValue;
			}
		};

		template <typename T, typename... Ts>
		struct Evaluator <T, Ts...> {
			static void makeMask(RealType& mask) {
				FamilyMask::setBit(mask, T::componentIndex);
				Evaluator<Ts...>::makeMask(mask);
			}

			static HandleType getMask() {
				RealType mask;
				makeMask(mask);
				return getHandle(mask);
			}
		};



		template <typename... Ts>
		struct MutableEvaluator;

		template <>
		struct MutableEvaluator <> {
			static RealType makeMask(RealType startValue) {
				return startValue;
			}
		};

		template <typename T, typename... Ts>
		struct MutableEvaluator <T, Ts...> {
			static void makeMask(RealType& mask) {
				if (std::is_const<T>::value) {
					FamilyMask::setBit(mask, T::componentIndex);
				}
				Evaluator<Ts...>::makeMask(mask);
			}

			static HandleType getMask() {
				RealType mask;
				makeMask(mask);
				return getHandle(mask);
			}
		};
	}

	class MaskStorageInterface
	{
	public:
		static void* createMaskStorage();
		static void setMaskStorage(void*);
	};

	using FamilyMaskType = FamilyMask::HandleType;
}