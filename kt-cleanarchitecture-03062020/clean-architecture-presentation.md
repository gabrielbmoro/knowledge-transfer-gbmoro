---
theme: 'night'
transition: 'slide'
highlightTheme: 'monokai'
logoImg: '/img/logo.png'
slideNumber: false
title: 'Clean Architecture to Android Development'
---

<!--Template used https://raw.githubusercontent.com/evilz/vscode-reveal/master/sample.md -->

### Clean Architecture to Android Development

_Applying SOLID concepts_

<small> 
  <strong>DG Conference Week</strong> <br /><br />
  Created by <i>Gabriel B. Moro - <a>moro@devgrid.co.uk</a></i> <br />
  </small>

---

### Summary

- Overview about the _Onion Approach_

- Dependency Rule

- Abstraction Concept

- Cake Recipe to Android

- SOLID Principles

- Final Consideration

---

### Onion Approach

<img src="/img/clean_architecture_image.svg" alt="...">

---

_Dependency_ between **UI** and **Presentation** class

```kotlin
class LoginActivity : Activity() {

  lateinit var viewModel : LoginViewModel
  lateinit var tvUserName : EditText
  lateinit var tvPassword : PasswordText
  lateinit var btnLogin : Button

  override fun onCreate() {
   	// binding

    // listeners
    btnLogin.setOnClickListener {
        viewModel.onLoginClickEvent(
        userName = tvUserName.text,
        password= tvPassword.text
      )
    }

    // observers
    viewModel.onLoginSuccess.observe(
      Observer<Boolean> { loginSuccess->
        if(loginSuccess) {
          finish()
          HomeScreen.launch()
        } else {
          showErrorMessage()
        }
      }
    )
  }
}
```

---

_Dependency_ between **Presentation** and **Use Case** class

```kotlin
class LoginViewModel : ViewModel() {

  val userUseCase by inject<UserUseCase>()

  val onLoginSuccess = LiveData<Boolean>()

  fun onLoginClickEvent(userName : String,password : Password) {

    val encryptedPassword = password.toEncryptedPassword()

    userUseCase.login(
      userName = userName, encryptedPassword = encryptedPassword,
      success = { onLoginSuccess.postValue(true) },
      error = { onLoginSuccess.postValue(false) }
    )
  }
}
```

---

_Dependency_ between **Use case** and **Entity** class

```kotlin
class UserUseCase {

    fun login(
        userName : String,
        encryptedPassword : String,
        success : (()->Unit),
        error : (()->Unit)
    ){
     	// call for server or some repository
    }
}
```

---

### Abstraction Concept

<img src="/img/abstraction_concept.svg" alt="...">

---

Is there a _“cake recipe”_ to implement the clean architecture to develop Android Apps?

---

<small>Is there a _“cake recipe”_ to implement the clean architecture to develop Android Apps?</small>

In my opinion **no**, but we can define a good template ;)

---

### SOLID Principles

**S**<small>ingle responsability</small>

**O**<small>pen-closed</small>

**L**<small>iscov Substitution</small>

**I**<small>nterface Segregation</small>

**D**<small>ependency Inversion</small>

---

### Single Responsability

<img src="/img/single-responsibility-example.png" alt="...">

---

### Open-closed

```kotlin
class LoginActivity : Activity() {

  override fun onCreate() { myCode }
}
```

```kotlin
class LoginActivity : Activity() {

  override fun onCreate() {
    super()
    myCode
  }
}
```

---

### Liscov Substitution

Look these two classes:

```kotlin
class Dog(val name : String) {

  fun walk() = println(“Walking…”)

  fun sleep() = println(“Sleeping …”)

}
```

```kotlin
class Pug(name : String) : Dog(name) {

  override fun walk() {
    super()
    sleep()
  }

}
```

---

### Liscov Substitution

```kotlin
class DogWalker {
  fun walk(dog : Dog, durationInMinutes:Int){
    object: CountDownTimer(durationInMinutes * 1000L, 200L) {
      override fun onTick(millisUntilFinished: Long) {
        dog.walk()
      }

    override fun onFinish() {
        dog.sleep()
      }
    }.start()
  }
}
```

```kotlin
fun main() {
  val dogWalker = DogWalker()
  dogWalker.walk(Dog(“Fred”), 500L)
}
```

---

### Interface Segregation

```kotlin
interface RecyclerViewListeners {
  fun onClick(v : View, position : Int)
  fun onLongPress(v : View, position : Int, timePressed : Int)
  fun onSingleTap(v : View)
  fun onSingleDown(v : View)
}
```

```kotlin
class RecyclerViewOnlyBasicEvents : RecyclerView(), RecyclerViewListeners {
  override fun onClick(v : View, position : Int){
    // Has implementation
  }
  override fun onLongPress(v : View, position : Int, timePressed : Int) {
    // Has implementation
  }
  override fun onSingleTap(v : View) {
    // Not necessary
  }
  override fun onSingleDown(v : View) {
    // Not necessary
  }
}
```

---

### Interface Segregation

```kotlin
interface RecyclerViewListeners {
  interface BasicEvents {
    fun onClick(v : View, position : Int)
    fun onLongPress(v : View, position : Int, timePressed : Int)
  }
  interface SingleTaps {
    fun onSingleTap(v : View)
    fun onSingleDown(v : View)
  }
}
```

```kotlin
class RecyclerViewOnlyBasicEvents : RecyclerView(), RecyclerViewListeners.BasicEvents {
  override fun onClick(v : View, position : Int){
    // Has implementation
  }
  override fun onLongPress(v : View, position : Int, timePressed : Int) {
    // Has implementation
  }
}
```

---

### Dependency Inversion

<img src="/img/dependency-inversion-1.png" height="400" alt="...">

---

### Dependency Inversion

<img src="/img/dependency-inversion-2.png" height="400" alt="...">

---

### Conclusions

> It is hard to solve all of the problems that we have when we are developing software with good quality.
> To combine factors such as _simplicity_, _performance_, and _efficiency_ are always a big challenge.
> For this reason, we build software in _teams_.

---

### Useful Links

- [Clean Architecture Tutorial for Android : Getting Started](https://www.raywenderlich.com/3595916-clean-architecture-tutorial-for-android-getting-started)

- [Essentials Components for Any Successful Android Project](https://www.poatek.com/2019/08/20/essential-components-for-any-successful-android-project)

- [Getting started with Android Jetpack](https://developer.android.com/jetpack/docs/getting-started/)
