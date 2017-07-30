; ModuleID = '/data/download/cmake/cmake-master/Source/kwsys/String.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define i32 @cmsysString_strcasecmp(i8* %lhs, i8* %rhs) #0 !dbg !4 {
entry:
  %lhs.addr = alloca i8*, align 8
  %rhs.addr = alloca i8*, align 8
  store i8* %lhs, i8** %lhs.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %lhs.addr, metadata !20, metadata !21), !dbg !22
  store i8* %rhs, i8** %rhs.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %rhs.addr, metadata !23, metadata !21), !dbg !24
  %0 = load i8*, i8** %lhs.addr, align 8, !dbg !25
  %1 = load i8*, i8** %rhs.addr, align 8, !dbg !26
  %call = call i32 @strcasecmp(i8* %0, i8* %1) #3, !dbg !27
  ret i32 %call, !dbg !28
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind readonly
declare i32 @strcasecmp(i8*, i8*) #2

; Function Attrs: nounwind uwtable
define i32 @cmsysString_strncasecmp(i8* %lhs, i8* %rhs, i64 %n) #0 !dbg !11 {
entry:
  %lhs.addr = alloca i8*, align 8
  %rhs.addr = alloca i8*, align 8
  %n.addr = alloca i64, align 8
  store i8* %lhs, i8** %lhs.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %lhs.addr, metadata !29, metadata !21), !dbg !30
  store i8* %rhs, i8** %rhs.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %rhs.addr, metadata !31, metadata !21), !dbg !32
  store i64 %n, i64* %n.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %n.addr, metadata !33, metadata !21), !dbg !34
  %0 = load i8*, i8** %lhs.addr, align 8, !dbg !35
  %1 = load i8*, i8** %rhs.addr, align 8, !dbg !36
  %2 = load i64, i64* %n.addr, align 8, !dbg !37
  %call = call i32 @strncasecmp(i8* %0, i8* %1, i64 %2) #3, !dbg !38
  ret i32 %call, !dbg !39
}

; Function Attrs: nounwind readonly
declare i32 @strncasecmp(i8*, i8*, i64) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!17, !18}
!llvm.ident = !{!19}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Source/kwsys/String.c", directory: "/data/download/cmake/cmake-master/Source/kwsys")
!2 = !{}
!3 = !{!4, !11}
!4 = distinct !DISubprogram(name: "cmsysString_strcasecmp", scope: !1, file: !1, line: 64, type: !5, isLocal: false, isDefinition: true, scopeLine: 65, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7, !8, !8}
!7 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!8 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !9, size: 64, align: 64)
!9 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !10)
!10 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!11 = distinct !DISubprogram(name: "cmsysString_strncasecmp", scope: !1, file: !1, line: 82, type: !12, isLocal: false, isDefinition: true, scopeLine: 83, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!12 = !DISubroutineType(types: !13)
!13 = !{!7, !8, !8, !14}
!14 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !15, line: 62, baseType: !16)
!15 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Source/kwsys")
!16 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!17 = !{i32 2, !"Dwarf Version", i32 4}
!18 = !{i32 2, !"Debug Info Version", i32 3}
!19 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!20 = !DILocalVariable(name: "lhs", arg: 1, scope: !4, file: !1, line: 64, type: !8)
!21 = !DIExpression()
!22 = !DILocation(line: 64, column: 40, scope: !4)
!23 = !DILocalVariable(name: "rhs", arg: 2, scope: !4, file: !1, line: 64, type: !8)
!24 = !DILocation(line: 64, column: 57, scope: !4)
!25 = !DILocation(line: 69, column: 21, scope: !4)
!26 = !DILocation(line: 69, column: 26, scope: !4)
!27 = !DILocation(line: 69, column: 10, scope: !4)
!28 = !DILocation(line: 69, column: 3, scope: !4)
!29 = !DILocalVariable(name: "lhs", arg: 1, scope: !11, file: !1, line: 82, type: !8)
!30 = !DILocation(line: 82, column: 41, scope: !11)
!31 = !DILocalVariable(name: "rhs", arg: 2, scope: !11, file: !1, line: 82, type: !8)
!32 = !DILocation(line: 82, column: 58, scope: !11)
!33 = !DILocalVariable(name: "n", arg: 3, scope: !11, file: !1, line: 82, type: !14)
!34 = !DILocation(line: 82, column: 70, scope: !11)
!35 = !DILocation(line: 87, column: 22, scope: !11)
!36 = !DILocation(line: 87, column: 27, scope: !11)
!37 = !DILocation(line: 87, column: 32, scope: !11)
!38 = !DILocation(line: 87, column: 10, scope: !11)
!39 = !DILocation(line: 87, column: 3, scope: !11)
