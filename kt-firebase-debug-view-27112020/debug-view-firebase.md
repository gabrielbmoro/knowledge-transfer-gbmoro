---
theme: "moon"
transition: "slide"
highlightTheme: "monokai"
logoImg: "/img/logo.png"
slideNumber: false
title: "Firebase DebugView"
---

<!--Template used https://raw.githubusercontent.com/evilz/vscode-reveal/master/sample.md -->

## Firebase DebugView

#### What is that?

DebugView is a tool provide by Firebase to see the raw event data logged by your app on development devices in near real-time.

---

#### How to use on Android?

- Enable the Analytics Debug mode on an Android Device:

```
adb shell setprop debug.firebase.analytics.app package_name
```

- Command to Disable the Analytics Debug mode:

```
adb shell setprop debug.firebase.analytics.app .none.
```

---

#### Useful link

[Firebase Documentation about DebugView](https://firebase.google.com/docs/analytics/debugview)
