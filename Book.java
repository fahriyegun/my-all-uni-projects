package entity;

/**
 * Created by Fahriye on 10.8.2016.
 */
import java.util.Date;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.Table;

//pojo class
@Entity
@Table(name = "book")
public class Book {
    public int book_id;
    public String book_name,author, genre;
    public int page, price;

    public Book() {
    }

    public Book(int book_id, String book_name, String author, String genre, int page, int price) {
        this.book_id = book_id;
        this.book_name = book_name;
        this.author = author;
        this.genre = genre;
        this.page = page;
        this.price = price;
    }

    @Id
    @Column(name = "book_id", unique = true, nullable = false, precision = 5, scale = 0)
    public int getBook_id() {
        return book_id;
    }

    public void setBook_id(int book_id) {
        this.book_id = book_id;
    }

    @Column(name = "book_name", nullable = false, length = 20)
    public String getBook_name() {
        return book_name;
    }

    public void setBook_name(String book_name) {
        this.book_name = book_name;
    }

    @Column(name = "author", nullable = false, length = 20)
    public String getAuthor() {
        return author;
    }

    public void setAuthor(String author) {
        this.author = author;
    }

    @Column(name = "genre", nullable = false, length = 20)
    public String getGenre() {
        return genre;
    }

    public void setGenre(String genre) {
        this.genre = genre;
    }

    @Column(name = "page", nullable = false, length = 20)
    public int getPage() {
        return page;
    }

    public void setPage(int page) {
        this.page = page;
    }

    @Column(name = "price", nullable = false, length = 20)
    public int getPrice() {
        return price;
    }

    public void setPrice(int price) {
        this.price = price;
    }












}
