---
theme: "moon"
transition: "slide"
highlightTheme: "monokai"
logoImg: "/img/logo.png"
slideNumber: false
title: "Unit Tests with Koin"
---

<!--Template used https://raw.githubusercontent.com/evilz/vscode-reveal/master/sample.md -->

# Unit Tests with Koin

---

Step 1: Add the gradle dependencies

```
// File: app->build.gradle


// General Dependencies
implementation 'org.koin:koin-androidx-scope:2.1.5'
implementation 'org.koin:koin-androidx-viewmodel:2.1.5'
implementation 'org.koin:koin-androidx-ext:2.1.5'

// Tests
testImplementation 'org.koin:koin-test:2.1.5'
```

---

Step 2: Create a base class


```kotlin

open class KoinUnitTest : KoinTest {

    private val fakeRepositoryModule = module{ ... }

    @get:Rule
    val koinTestRule = KoinTestRule.create {
        androidLogger(Level.ERROR)
        androidContext(Mockito.mock(Context::class.java))
        modules(fakeRepositoryModule, usecaseModule)
    }
}

```

---

Step 3: Write the unit test

```kotlin
class PopularMoviesUseCaseTest : KoinUnitTest() {

    @Test
    fun `popularMoviesUseCase using the correct repository`() {
        // given
        val popularUseCaseTest by inject<PopularMoviesUseCase>()

        // when
        val repository = popularUseCaseTest.repository

        // then
        Truth.assertThat(repository).isInstanceOf(
            ApiRepositoryImpl::class.java
        )
    }
```


---

### Code Example

[Here](https://github.com/gabrielbmoro/MovieDBApi/tree/master/android-native/ProgrammingChallenge)