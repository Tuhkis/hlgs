package hlgs;

class Test {
  public static function main() {
    var app: AppDesc = new AppDesc();
    var cb: CommandBuffer;

    Gs.create(app);

    cb = new CommandBuffer();

    while (Gs.appIsRunning()) {
      cb.renderpassBegin();
        cb.clear(1.0, 0.2, 0.2);
      cb.renderpassEnd();
      cb.submit();
      Gs.frame();
    }
    cb.dispose();
    cb = null;
    trace('All works!');
  }
}

