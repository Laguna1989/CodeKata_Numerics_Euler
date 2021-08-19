import pytest

from euler import explicit_euler_integrate_one_step, explicit_euler_integrate


def test_calls_function():
    has_been_called = False

    def f(x):
        nonlocal has_been_called
        has_been_called = True
        return 5.0

    explicit_euler_integrate_one_step(f, 0, 0)

    assert has_been_called == True


def const_function(x):
    return 5.0


def test_returns_zero_for_delta_zero():
    assert 1.0 == explicit_euler_integrate_one_step(const_function, 1.0, 0.0)


def test_returns_correct_value_for_delta_one():
    assert 5.0 == explicit_euler_integrate_one_step(const_function, 0.0, 1.0)


def test_returns_correct_value_for_delta_two():
    assert 10.0 == explicit_euler_integrate_one_step(const_function, 0.0, 2.0)


def test_returns_correct_value_for_delta_00001():
    assert 5.0 * 0.00001 == explicit_euler_integrate_one_step(const_function, 0.0, 0.00001)


@pytest.mark.parametrize("delta, expected_size", [(1.5, 1),  # only start point contained
                                                  (1.0, 2),  # start and end point
                                                  (0.5, 3),  # start, end and one midpoint
                                                  (0.1, 11)])  # start, end and 9 points contained
def test_euler_returned_map_size(delta, expected_size):
    values = explicit_euler_integrate(const_function, 0.0, delta, 0.0, 1.0)
    assert len(values) == expected_size


@pytest.mark.parametrize("delta", [1.0, 0.5, 0.1])
def test_euler_returned_map_contains_trange_start(delta):
    values = explicit_euler_integrate(const_function, 0.0, delta, 0.0, 1.0)
    assert 0.0 in values.keys()


@pytest.mark.parametrize("delta", [1.0, 0.5])
def test_euler_returned_map_contains_trange_end(delta):
    values = explicit_euler_integrate(const_function, 0.0, delta, 0.0, 1.0)
    assert 1.0 in values.keys()


@pytest.mark.parametrize("delta", [1.0, 0.5])
def test_euler_returned_map_contains_value_for_one_integration_point(delta):
    values = explicit_euler_integrate(const_function, 0.0, delta, 0.0, 1.0)

    value = values[1.0]
    deviation = value - const_function(1.0)
    assert deviation < 1e-5
