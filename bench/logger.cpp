/// Format string and write it to null.

#include <benchmark/benchmark.h>

#include <blackhole/logger.hpp>

namespace blackhole {
namespace benchmark {

static
void
literal(::benchmark::State& state) {
    logger_t log({});

    while (state.KeepRunning()) {
        log.info("[::] - esafronov [10/Oct/2000:13:55:36 -0700] 'GET /porn.png HTTP/1.0' 200 2326");
    }

    state.SetItemsProcessed(state.iterations());
}

static
void
literal_reject(::benchmark::State& state) {
    logger_t log({});
    log.filter([](const record_t&) -> bool {
        return false;
    });

    while (state.KeepRunning()) {
        log.info("[::] - esafronov [10/Oct/2000:13:55:36 -0700] 'GET /porn.png HTTP/1.0' 200 2326");
    }

    state.SetItemsProcessed(state.iterations());
}

static
void
string(::benchmark::State& state) {
    logger_t log({});

    const std::string string("[::] - esafronov [10/Oct/2000:13:55:36 -0700] 'GET /porn.png HTTP/1.0' 200 2326");
    while (state.KeepRunning()) {
        log.info(string);
    }

    state.SetItemsProcessed(state.iterations());
}

static
void
literal_with_arg(::benchmark::State& state) {
    logger_t log({});

    while (state.KeepRunning()) {
        log.info("[::] - esafronov [10/Oct/2000:13:55:36 -0700] 'GET {} HTTP/1.0' 200 2326",
            "/porn.png"
        );
    }

    state.SetItemsProcessed(state.iterations());
}

static
void
literal_with_args(::benchmark::State& state) {
    logger_t log({});

    while (state.KeepRunning()) {
        log.info("{} - {} [{}] 'GET {} HTTP/1.0' {} {}",
            "[::]",
            "esafronov",
            "10/Oct/2000:13:55:36 -0700",
            "/porn.png",
            200,
            2326
        );
    }

    state.SetItemsProcessed(state.iterations());
}

static
void
cpp14_formatter_with_args(::benchmark::State& state) {
    logger_t log({});

    while (state.KeepRunning()) {
        constexpr auto formatter = blackhole::detail::formatter<
            blackhole::detail::literal_count("{} - {} [{}] 'GET {} HTTP/1.0' {} {}")
        >("{} - {} [{}] 'GET {} HTTP/1.0' {} {}");

        log.info(formatter,
            "[::]",
            "esafronov",
            "10/Oct/2000:13:55:36 -0700",
            "/porn.png",
            200,
            2326
        );
    }

    state.SetItemsProcessed(state.iterations());
}

static
void
literal_with_attributes(::benchmark::State& state) {
    logger_t log({});

    while (state.KeepRunning()) {
        log.info("[::] - esafronov [10/Oct/2000:13:55:36 -0700] 'GET /porn.png HTTP/1.0' 200 2326", {
            {"key#1", attribute_value_t(42)},
            {"key#2", attribute_value_t(3.1415)},
            {"key#3", attribute_value_t("value")}
        });
    }

    state.SetItemsProcessed(state.iterations());
}

static
void
literal_with_args_and_attributes(::benchmark::State& state) {
    logger_t log({});

    while (state.KeepRunning()) {
        log.info("{} - {} [{}] 'GET {} HTTP/1.0' {} {}",
            {
                {"key#1", attribute_value_t(42)},
                {"key#2", attribute_value_t(3.1415)},
                {"key#3", attribute_value_t("value")}
            },
            "[::]",
            "esafronov",
            "10/Oct/2000:13:55:36 -0700",
            "/porn.png",
            200,
            2326
        );
    }

    state.SetItemsProcessed(state.iterations());
}

static
void
literal_with_args_and_attributes_and_wrapper(::benchmark::State& state) {
    logger_t log({});
    wrapper_t wrapper{log, {
        {"key#0", owned_attribute_value_t(500)},
        {"key#1", owned_attribute_value_t("value#1")}
    }};

    while (state.KeepRunning()) {
        wrapper.info("{} - {} [{}] 'GET {} HTTP/1.0' {} {}",
            {
                {"key#1", attribute_value_t(42)},
                {"key#2", attribute_value_t(3.1415)},
                {"key#3", attribute_value_t("value")}
            },
            "[::]",
            "esafronov",
            "10/Oct/2000:13:55:36 -0700",
            "/porn.png",
            200,
            2326
        );
    }

    state.SetItemsProcessed(state.iterations());
}

BENCHMARK(literal);
BENCHMARK(literal_reject);
BENCHMARK(string);
BENCHMARK(literal_with_arg);
BENCHMARK(literal_with_args);
BENCHMARK(cpp14_formatter_with_args);

BENCHMARK(literal_with_attributes);
BENCHMARK(literal_with_args_and_attributes);

BENCHMARK(literal_with_args_and_attributes_and_wrapper);

}  // namespace benchmark
}  // namespace blackhole