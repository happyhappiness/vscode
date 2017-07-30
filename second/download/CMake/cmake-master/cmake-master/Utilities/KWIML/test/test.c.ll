; ModuleID = '/data/download/cmake/cmake-master/Utilities/KWIML/test/test.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define i32 @main() #0 !dbg !4 {
entry:
  %retval = alloca i32, align 4
  %result = alloca i32, align 4
  store i32 0, i32* %retval, align 4
  call void @llvm.dbg.declare(metadata i32* %result, metadata !11, metadata !12), !dbg !13
  store i32 1, i32* %result, align 4, !dbg !13
  %call = call i32 @test_abi_C(), !dbg !14
  %tobool = icmp ne i32 %call, 0, !dbg !14
  br i1 %tobool, label %land.rhs, label %land.end, !dbg !15

land.rhs:                                         ; preds = %entry
  %0 = load i32, i32* %result, align 4, !dbg !16
  %tobool1 = icmp ne i32 %0, 0, !dbg !18
  br label %land.end

land.end:                                         ; preds = %land.rhs, %entry
  %1 = phi i1 [ false, %entry ], [ %tobool1, %land.rhs ]
  %land.ext = zext i1 %1 to i32, !dbg !19
  store i32 %land.ext, i32* %result, align 4, !dbg !21
  %call2 = call i32 @test_int_C(), !dbg !22
  %tobool3 = icmp ne i32 %call2, 0, !dbg !22
  br i1 %tobool3, label %land.rhs4, label %land.end6, !dbg !23

land.rhs4:                                        ; preds = %land.end
  %2 = load i32, i32* %result, align 4, !dbg !24
  %tobool5 = icmp ne i32 %2, 0, !dbg !25
  br label %land.end6

land.end6:                                        ; preds = %land.rhs4, %land.end
  %3 = phi i1 [ false, %land.end ], [ %tobool5, %land.rhs4 ]
  %land.ext7 = zext i1 %3 to i32, !dbg !26
  store i32 %land.ext7, i32* %result, align 4, !dbg !27
  %call8 = call i32 @test_include_C(), !dbg !28
  %tobool9 = icmp ne i32 %call8, 0, !dbg !28
  br i1 %tobool9, label %land.rhs10, label %land.end12, !dbg !29

land.rhs10:                                       ; preds = %land.end6
  %4 = load i32, i32* %result, align 4, !dbg !30
  %tobool11 = icmp ne i32 %4, 0, !dbg !31
  br label %land.end12

land.end12:                                       ; preds = %land.rhs10, %land.end6
  %5 = phi i1 [ false, %land.end6 ], [ %tobool11, %land.rhs10 ]
  %land.ext13 = zext i1 %5 to i32, !dbg !32
  store i32 %land.ext13, i32* %result, align 4, !dbg !33
  %call14 = call i32 @test_abi_CXX(), !dbg !34
  %tobool15 = icmp ne i32 %call14, 0, !dbg !34
  br i1 %tobool15, label %land.rhs16, label %land.end18, !dbg !35

land.rhs16:                                       ; preds = %land.end12
  %6 = load i32, i32* %result, align 4, !dbg !36
  %tobool17 = icmp ne i32 %6, 0, !dbg !37
  br label %land.end18

land.end18:                                       ; preds = %land.rhs16, %land.end12
  %7 = phi i1 [ false, %land.end12 ], [ %tobool17, %land.rhs16 ]
  %land.ext19 = zext i1 %7 to i32, !dbg !38
  store i32 %land.ext19, i32* %result, align 4, !dbg !39
  %call20 = call i32 @test_int_CXX(), !dbg !40
  %tobool21 = icmp ne i32 %call20, 0, !dbg !40
  br i1 %tobool21, label %land.rhs22, label %land.end24, !dbg !41

land.rhs22:                                       ; preds = %land.end18
  %8 = load i32, i32* %result, align 4, !dbg !42
  %tobool23 = icmp ne i32 %8, 0, !dbg !43
  br label %land.end24

land.end24:                                       ; preds = %land.rhs22, %land.end18
  %9 = phi i1 [ false, %land.end18 ], [ %tobool23, %land.rhs22 ]
  %land.ext25 = zext i1 %9 to i32, !dbg !44
  store i32 %land.ext25, i32* %result, align 4, !dbg !45
  %call26 = call i32 @test_include_CXX(), !dbg !46
  %tobool27 = icmp ne i32 %call26, 0, !dbg !46
  br i1 %tobool27, label %land.rhs28, label %land.end30, !dbg !47

land.rhs28:                                       ; preds = %land.end24
  %10 = load i32, i32* %result, align 4, !dbg !48
  %tobool29 = icmp ne i32 %10, 0, !dbg !49
  br label %land.end30

land.end30:                                       ; preds = %land.rhs28, %land.end24
  %11 = phi i1 [ false, %land.end24 ], [ %tobool29, %land.rhs28 ]
  %land.ext31 = zext i1 %11 to i32, !dbg !50
  store i32 %land.ext31, i32* %result, align 4, !dbg !51
  %12 = load i32, i32* %result, align 4, !dbg !52
  %tobool32 = icmp ne i32 %12, 0, !dbg !52
  %cond = select i1 %tobool32, i32 0, i32 1, !dbg !52
  ret i32 %cond, !dbg !53
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare i32 @test_abi_C() #2

declare i32 @test_int_C() #2

declare i32 @test_include_C() #2

declare i32 @test_abi_CXX() #2

declare i32 @test_int_CXX() #2

declare i32 @test_include_CXX() #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!8, !9}
!llvm.ident = !{!10}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/KWIML/test/test.c", directory: "/data/download/cmake/cmake-master/Utilities/KWIML/test")
!2 = !{}
!3 = !{!4}
!4 = distinct !DISubprogram(name: "main", scope: !1, file: !1, line: 19, type: !5, isLocal: false, isDefinition: true, scopeLine: 20, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7}
!7 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!8 = !{i32 2, !"Dwarf Version", i32 4}
!9 = !{i32 2, !"Debug Info Version", i32 3}
!10 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!11 = !DILocalVariable(name: "result", scope: !4, file: !1, line: 21, type: !7)
!12 = !DIExpression()
!13 = !DILocation(line: 21, column: 7, scope: !4)
!14 = !DILocation(line: 23, column: 12, scope: !4)
!15 = !DILocation(line: 23, column: 25, scope: !4)
!16 = !DILocation(line: 23, column: 28, scope: !17)
!17 = !DILexicalBlockFile(scope: !4, file: !1, discriminator: 1)
!18 = !DILocation(line: 23, column: 25, scope: !17)
!19 = !DILocation(line: 23, column: 25, scope: !20)
!20 = !DILexicalBlockFile(scope: !4, file: !1, discriminator: 2)
!21 = !DILocation(line: 23, column: 10, scope: !20)
!22 = !DILocation(line: 24, column: 12, scope: !4)
!23 = !DILocation(line: 24, column: 25, scope: !4)
!24 = !DILocation(line: 24, column: 28, scope: !17)
!25 = !DILocation(line: 24, column: 25, scope: !17)
!26 = !DILocation(line: 24, column: 25, scope: !20)
!27 = !DILocation(line: 24, column: 10, scope: !20)
!28 = !DILocation(line: 25, column: 12, scope: !4)
!29 = !DILocation(line: 25, column: 29, scope: !4)
!30 = !DILocation(line: 25, column: 32, scope: !17)
!31 = !DILocation(line: 25, column: 29, scope: !17)
!32 = !DILocation(line: 25, column: 29, scope: !20)
!33 = !DILocation(line: 25, column: 10, scope: !20)
!34 = !DILocation(line: 28, column: 12, scope: !4)
!35 = !DILocation(line: 28, column: 27, scope: !4)
!36 = !DILocation(line: 28, column: 30, scope: !17)
!37 = !DILocation(line: 28, column: 27, scope: !17)
!38 = !DILocation(line: 28, column: 27, scope: !20)
!39 = !DILocation(line: 28, column: 10, scope: !20)
!40 = !DILocation(line: 29, column: 12, scope: !4)
!41 = !DILocation(line: 29, column: 27, scope: !4)
!42 = !DILocation(line: 29, column: 30, scope: !17)
!43 = !DILocation(line: 29, column: 27, scope: !17)
!44 = !DILocation(line: 29, column: 27, scope: !20)
!45 = !DILocation(line: 29, column: 10, scope: !20)
!46 = !DILocation(line: 30, column: 12, scope: !4)
!47 = !DILocation(line: 30, column: 31, scope: !4)
!48 = !DILocation(line: 30, column: 34, scope: !17)
!49 = !DILocation(line: 30, column: 31, scope: !17)
!50 = !DILocation(line: 30, column: 31, scope: !20)
!51 = !DILocation(line: 30, column: 10, scope: !20)
!52 = !DILocation(line: 32, column: 10, scope: !4)
!53 = !DILocation(line: 32, column: 3, scope: !4)
