; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmcurl/lib/curl_memrchr.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define i8* @Curl_memrchr(i8* %s, i32 %c, i64 %n) #0 !dbg !7 {
entry:
  %retval = alloca i8*, align 8
  %s.addr = alloca i8*, align 8
  %c.addr = alloca i32, align 4
  %n.addr = alloca i64, align 8
  %p = alloca i8*, align 8
  %q = alloca i8*, align 8
  store i8* %s, i8** %s.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %s.addr, metadata !19, metadata !20), !dbg !21
  store i32 %c, i32* %c.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %c.addr, metadata !22, metadata !20), !dbg !23
  store i64 %n, i64* %n.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %n.addr, metadata !24, metadata !20), !dbg !25
  call void @llvm.dbg.declare(metadata i8** %p, metadata !26, metadata !20), !dbg !29
  %0 = load i8*, i8** %s.addr, align 8, !dbg !30
  store i8* %0, i8** %p, align 8, !dbg !29
  call void @llvm.dbg.declare(metadata i8** %q, metadata !31, metadata !20), !dbg !32
  %1 = load i8*, i8** %s.addr, align 8, !dbg !33
  store i8* %1, i8** %q, align 8, !dbg !32
  %2 = load i64, i64* %n.addr, align 8, !dbg !34
  %sub = sub i64 %2, 1, !dbg !35
  %3 = load i8*, i8** %p, align 8, !dbg !36
  %add.ptr = getelementptr inbounds i8, i8* %3, i64 %sub, !dbg !36
  store i8* %add.ptr, i8** %p, align 8, !dbg !36
  br label %while.cond, !dbg !37

while.cond:                                       ; preds = %if.end, %entry
  %4 = load i8*, i8** %p, align 8, !dbg !38
  %5 = load i8*, i8** %q, align 8, !dbg !40
  %cmp = icmp uge i8* %4, %5, !dbg !41
  br i1 %cmp, label %while.body, label %while.end, !dbg !42

while.body:                                       ; preds = %while.cond
  %6 = load i8*, i8** %p, align 8, !dbg !43
  %7 = load i8, i8* %6, align 1, !dbg !46
  %conv = zext i8 %7 to i32, !dbg !46
  %8 = load i32, i32* %c.addr, align 4, !dbg !47
  %conv1 = trunc i32 %8 to i8, !dbg !48
  %conv2 = zext i8 %conv1 to i32, !dbg !48
  %cmp3 = icmp eq i32 %conv, %conv2, !dbg !49
  br i1 %cmp3, label %if.then, label %if.end, !dbg !50

if.then:                                          ; preds = %while.body
  %9 = load i8*, i8** %p, align 8, !dbg !51
  store i8* %9, i8** %retval, align 8, !dbg !52
  br label %return, !dbg !52

if.end:                                           ; preds = %while.body
  %10 = load i8*, i8** %p, align 8, !dbg !53
  %incdec.ptr = getelementptr inbounds i8, i8* %10, i32 -1, !dbg !53
  store i8* %incdec.ptr, i8** %p, align 8, !dbg !53
  br label %while.cond, !dbg !54

while.end:                                        ; preds = %while.cond
  store i8* null, i8** %retval, align 8, !dbg !56
  br label %return, !dbg !56

return:                                           ; preds = %while.end, %if.then
  %11 = load i8*, i8** %retval, align 8, !dbg !57
  ret i8* %11, !dbg !57
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!16, !17}
!llvm.ident = !{!18}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !6)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/curl_memrchr.c", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!2 = !{}
!3 = !{!4, !5}
!4 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!5 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!6 = !{!7}
!7 = distinct !DISubprogram(name: "Curl_memrchr", scope: !1, file: !1, line: 45, type: !8, isLocal: false, isDefinition: true, scopeLine: 46, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!8 = !DISubroutineType(types: !9)
!9 = !{!5, !10, !12, !13}
!10 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !11, size: 64, align: 64)
!11 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!12 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!13 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !14, line: 62, baseType: !15)
!14 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!15 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!16 = !{i32 2, !"Dwarf Version", i32 4}
!17 = !{i32 2, !"Debug Info Version", i32 3}
!18 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!19 = !DILocalVariable(name: "s", arg: 1, scope: !7, file: !1, line: 45, type: !10)
!20 = !DIExpression()
!21 = !DILocation(line: 45, column: 26, scope: !7)
!22 = !DILocalVariable(name: "c", arg: 2, scope: !7, file: !1, line: 45, type: !12)
!23 = !DILocation(line: 45, column: 33, scope: !7)
!24 = !DILocalVariable(name: "n", arg: 3, scope: !7, file: !1, line: 45, type: !13)
!25 = !DILocation(line: 45, column: 43, scope: !7)
!26 = !DILocalVariable(name: "p", scope: !7, file: !1, line: 47, type: !27)
!27 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !28, size: 64, align: 64)
!28 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !4)
!29 = !DILocation(line: 47, column: 24, scope: !7)
!30 = !DILocation(line: 47, column: 28, scope: !7)
!31 = !DILocalVariable(name: "q", scope: !7, file: !1, line: 48, type: !27)
!32 = !DILocation(line: 48, column: 24, scope: !7)
!33 = !DILocation(line: 48, column: 28, scope: !7)
!34 = !DILocation(line: 50, column: 8, scope: !7)
!35 = !DILocation(line: 50, column: 10, scope: !7)
!36 = !DILocation(line: 50, column: 5, scope: !7)
!37 = !DILocation(line: 52, column: 3, scope: !7)
!38 = !DILocation(line: 52, column: 9, scope: !39)
!39 = !DILexicalBlockFile(scope: !7, file: !1, discriminator: 1)
!40 = !DILocation(line: 52, column: 14, scope: !39)
!41 = !DILocation(line: 52, column: 11, scope: !39)
!42 = !DILocation(line: 52, column: 3, scope: !39)
!43 = !DILocation(line: 53, column: 9, scope: !44)
!44 = distinct !DILexicalBlock(scope: !45, file: !1, line: 53, column: 8)
!45 = distinct !DILexicalBlock(scope: !7, file: !1, line: 52, column: 17)
!46 = !DILocation(line: 53, column: 8, scope: !44)
!47 = !DILocation(line: 53, column: 29, scope: !44)
!48 = !DILocation(line: 53, column: 14, scope: !44)
!49 = !DILocation(line: 53, column: 11, scope: !44)
!50 = !DILocation(line: 53, column: 8, scope: !45)
!51 = !DILocation(line: 54, column: 22, scope: !44)
!52 = !DILocation(line: 54, column: 7, scope: !44)
!53 = !DILocation(line: 55, column: 6, scope: !45)
!54 = !DILocation(line: 52, column: 3, scope: !55)
!55 = !DILexicalBlockFile(scope: !7, file: !1, discriminator: 2)
!56 = !DILocation(line: 58, column: 3, scope: !7)
!57 = !DILocation(line: 59, column: 1, scope: !7)
