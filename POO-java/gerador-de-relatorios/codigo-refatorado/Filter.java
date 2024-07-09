import java.util.List;

public interface Filter {
    public boolean select(Produto product, List<String> parameter);
}