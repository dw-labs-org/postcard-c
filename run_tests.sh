cargo test --manifest-path test/rust/Cargo.toml

for f in test/bin/*; do    
    if [ -f $f ] && [ -x $f ]; then
        ./$f
    fi
done

