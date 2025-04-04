gtest = subproject('gtest')
gtest_dep = gtest.get_variable('gtest_dep')
gmock_dep = gtest.get_variable('gmock_dep')
icu4c = subproject('icu')
icuuc_dep = icu4c.get_variable('icuuc_dep')
icui18n_dep = icu4c.get_variable('icui18n_dep')

greek_tests = executable('greek_tests',
  [
    'test_this.cpp',
  ],
  dependencies: [icuuc_dep, icui18n_dep, gtest_dep, gmock_dep],
)

test('greek_tests', greek_tests, suite: 'greek', args: [])
