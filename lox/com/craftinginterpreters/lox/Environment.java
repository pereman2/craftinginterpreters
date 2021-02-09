package com.craftinginterpreters.lox;

import java.util.HashMap;
import java.util.Map;

class Environment {
    private final Map<String, Object> values = new HashMap<>();
    final Environment enclosing;
    private boolean exit = false;
    private boolean loop = false;

    Environment() {
        enclosing = null;
    }

    Environment(Environment enclosing, boolean loop) {
        this.enclosing = enclosing;
        this.loop = loop;
    }

    void define(String name, Object value) {
        values.put(name, value);
    }

    boolean isLoopEnvironment () {
        return this.loop;
    }
    void signalBreak() {
        this.exit = true;
    }

    boolean breakSignaled() {
        return this.exit;
    }

    Object get(Token name) {
        if (values.containsKey(name.lexeme)) {
            return values.get(name.lexeme);
        }

        if(enclosing != null) return enclosing.get(name);

        throw new RuntimeError(name, "Undefined variable '" + name.lexeme + "'.");
    }

    void assign(Token name, Object value) {
        if (values.containsKey(name.lexeme)) {
            values.put(name.lexeme, value);
            return;
        }

        if(enclosing != null) {
            enclosing.assign(name, value);
            return;
        } 

        throw new RuntimeError(name, "Undefined variable '" + name.lexeme + "'.");
    }

}