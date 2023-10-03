package hlgs;

class Test {
  public static function main() {
    var app: AppDesc = new AppDesc();
    var cb: CommandBuffer;

    Gs.create(app);

    cb = new CommandBuffer();

    var data: Array<Single> = [1.5, 1.2, 2.3];
    var carr: CArrayFloat = new CArrayFloat(3);
    carr.dispose();
    var vbo: VertexBuffer = new VertexBuffer(data);

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

