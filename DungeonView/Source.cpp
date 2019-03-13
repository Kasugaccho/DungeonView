#include <cstdint>

namespace dtl::camera {

	class SampleDungeonViewDraw {
	public:
		constexpr SampleDungeonViewDraw() noexcept = default;
		template<typename Matrix_>
		constexpr void draw([[maybe_unused]]const Matrix_& matrix_, [[maybe_unused]]const std::int_fast32_t x_, [[maybe_unused]]const std::int_fast32_t y_, [[maybe_unused]]const std::int_fast32_t array_x_, [[maybe_unused]]const std::int_fast32_t array_y_, [[maybe_unused]]const std::int_fast32_t draw_x_, [[maybe_unused]]const std::int_fast32_t draw_y_, [[maybe_unused]]const std::int_fast32_t w_, [[maybe_unused]]const std::int_fast32_t h_) const noexcept {}
	};

	class DungeonView {
	private:
		//画面の幅・高さ
		std::int_fast32_t window_width{};
		std::int_fast32_t window_height{};
		//画面の始点座標
		std::int_fast32_t window_start_x{};
		std::int_fast32_t window_start_y{};
		//画面の終点座標
		std::int_fast32_t window_end_x{};
		std::int_fast32_t window_end_y{};
		//画面の中心座標
		std::int_fast32_t window_center_x{};
		std::int_fast32_t window_center_y{};
		//1マスのピクセル数
		std::int_fast32_t pixel_width{};
		std::int_fast32_t pixel_height{};
		//画面内のマスの数
		double cell_width{};
		double cell_height{};
		//視点座標
		double target_x{};
		double target_y{};
	public:

		constexpr void setTarget(const double target_x_, const double target_y_) noexcept {
			target_x = target_x_;
			target_y = target_y_;
		}
		constexpr void checkTarget(const double x_, const double y_) noexcept {
			while (target_x < 0) target_x += x_;
			while (target_y < 0) target_y += x_;
			while (target_x >= x_) target_x -= x_;
			while (target_y >= y_) target_y -= y_;
		}
		constexpr void checkTarget(double& target_x_, double& target_y_, const double x_, const double y_) const noexcept {
			while (target_x_ < 0) target_x_ += x_;
			while (target_y_ < 0) target_y_ += x_;
			while (target_x_ >= x_) target_x_ -= x_;
			while (target_y_ >= y_) target_y_ -= y_;
		}

		//コンストラクタ
		constexpr DungeonView(const std::int_fast32_t window_width_, const std::int_fast32_t window_height_, const std::int_fast32_t pixel_width_, const std::int_fast32_t pixel_height_, const double target_x_, const double target_y_) noexcept
			:window_width(window_width_),
			window_height(window_height_),
			window_start_x(0),
			window_start_y(0),
			window_end_x(window_width_),
			window_end_y(window_height_),
			window_center_x(window_width_ / 2),
			window_center_y(window_height_ / 2),
			pixel_width(pixel_width_),
			pixel_height(pixel_height_),
			cell_width(window_width_ / static_cast<double>(pixel_width_)),
			cell_height(window_height_ / static_cast<double>(pixel_height_)),
			target_x(target_x_),
			target_y(target_y_) {}



		template<typename Matrix_, typename View_Class_>
		constexpr void draw(Matrix_&& matrix_, const std::int_fast32_t x_, const std::int_fast32_t y_, View_Class_&& view_class_) const noexcept {

			const std::int_fast32_t target_int_x{ (target_x == static_cast<double>(static_cast<std::int_fast32_t>(target_x))) ? static_cast<std::int_fast32_t>(target_x) : static_cast<std::int_fast32_t>(target_x) + 1 };
			const std::int_fast32_t target_int_y{ (target_y == static_cast<double>(static_cast<std::int_fast32_t>(target_y))) ? static_cast<std::int_fast32_t>(target_y) : static_cast<std::int_fast32_t>(target_y) + 1 };
			const std::int_fast32_t draw_position_x{ (target_x == static_cast<double>(static_cast<std::int_fast32_t>(target_x))) ? window_center_x : window_center_x - static_cast<std::int_fast32_t>((target_x - static_cast<double>(static_cast<std::int_fast32_t>(target_x)))*static_cast<double>(pixel_width)) };
			const std::int_fast32_t draw_position_y{ (target_y == static_cast<double>(static_cast<std::int_fast32_t>(target_y))) ? window_center_y : window_center_y - static_cast<std::int_fast32_t>((target_y - static_cast<double>(static_cast<std::int_fast32_t>(target_y)))*static_cast<double>(pixel_height)) };

			for (std::int_fast32_t i{ draw_position_y - pixel_height }, draw_y{ target_int_y - 1 }; i > (window_start_y - pixel_height); i -= pixel_height, --draw_y) {
				while (draw_y < 0) draw_y += y_;
				if (draw_y >= y_) draw_y %= y_;
				//左下
				for (std::int_fast32_t j{ draw_position_x - pixel_width }, draw_x{ target_int_x - 1 }; j > (window_start_x - pixel_width); j -= pixel_width, --draw_x) {
					while (draw_x < 0) draw_x += x_;
					if (draw_x >= x_) draw_x %= x_;
					view_class_.draw(matrix_, x_, y_, draw_x, draw_y, j, i, pixel_width, pixel_height);
				}
				//右下
				for (std::int_fast32_t j{ draw_position_x }, draw_x{ target_int_x }; j < window_end_x; j += pixel_width, ++draw_x) {
					if (draw_x >= x_) draw_x %= x_;
					while (draw_x < 0) draw_x += x_;
					view_class_.draw(matrix_, x_, y_, draw_x, draw_y, j, i, pixel_width, pixel_height);
				}
			}
			for (std::int_fast32_t i{ draw_position_y }, draw_y{ target_int_y }; i < window_end_y; i += pixel_height, ++draw_y) {
				if (draw_y >= y_) draw_y %= y_;
				while (draw_y < 0) draw_y += y_;
				//左下
				for (std::int_fast32_t j{ draw_position_x - pixel_width }, draw_x{ target_int_x - 1 }; j > (window_start_x - pixel_width); j -= pixel_width, --draw_x) {
					while (draw_x < 0) draw_x += x_;
					if (draw_x >= x_) draw_x %= x_;
					view_class_.draw(matrix_, x_, y_, draw_x, draw_y, j, i, pixel_width, pixel_height);
				}
				//右下
				for (std::int_fast32_t j{ draw_position_x }, draw_x{ target_int_x }; j < window_end_x; j += pixel_width, ++draw_x) {
					if (draw_x >= x_) draw_x %= x_;
					while (draw_x < 0) draw_x += x_;
					view_class_.draw(matrix_, x_, y_, draw_x, draw_y, j, i, pixel_width, pixel_height);
				}
			}
		}
		template<typename Matrix_>
		constexpr void draw(Matrix_&& matrix_, const std::int_fast32_t x_, const std::int_fast32_t y_) const noexcept {
			draw(matrix_, x_, y_, SampleDungeonViewDraw());
		}

	};

}

int main() {



	return 0;
}