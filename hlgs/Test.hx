package hlgs;

class Test {
  public static function main() {
    var app: AppDesc = new AppDesc();

    Gs.create(app);
    while (Gs.appIsRunning()) {
      Gs.frame();
    }
    trace('All works!');
  }
}

