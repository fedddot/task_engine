#ifndef	ENGINE_HPP
#define	ENGINE_HPP

namespace engine {
	template <class Traw_data, class Treport>
	class Engine {
	public:
		virtual ~Engine() noexcept = default;
		virtual Treport run_task(const Traw_data& cfg) const = 0;
	};
}

#endif // ENGINE_HPP